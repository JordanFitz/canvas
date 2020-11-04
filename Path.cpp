#include <vector>
#include <sstream>

#include <SFML/Graphics.hpp>

#include "Path.hpp"

Path::Path() :
    m_closed(false),
    m_computed(false),
    m_lineWidth(-1),
    m_lineJoin(LineJoin::Miter)
{}

Path::~Path()
{
    for (auto it = m_lines.begin(); it < m_lines.end(); it++)
        delete* it;

    for (auto it = m_connectors.begin(); it < m_connectors.end(); it++)
        delete* it;

    m_vertices.clear();
    m_lines.clear();
    m_connectors.clear();
}

void Path::reset()
{
    m_closed = false;
    m_computed = false;
    m_vertices.clear();
}

void Path::close()
{
    if (m_closed) return;

    m_closed = true;
    m_computed = false;

    auto back = m_vertices.front();
    m_vertices.push_back(back);
}

void Path::addVertex(float x, float y)
{
    if (m_closed) return;
    m_vertices.push_back(sf::Vector2f(x, y));
    m_computed = false;
}

void Path::_computeVertices(float lineWidth, sf::Color color)
{   
    if (m_vertices.size() < 2) return;

    size_t i = 0;
    for (auto it = m_vertices.begin(); it < m_vertices.end(); it++)
    {
        if ((it + 1) == m_vertices.end())
        {
            break;
        }

        sf::Vector2f vertex = *it;
        sf::Vector2f next = *(it + 1);

        sf::Vector2f delta = vertex - next;

        const double angle = atan2(delta.y, delta.x),
            p1 = angle - PI_2,
            p2 = angle + PI_2;

        sf::VertexArray* vertexArray;

        if (m_lines.size() < m_vertices.size() - 1)
        {
            vertexArray = new sf::VertexArray(sf::Quads, 4);
        }
        else
        {
            vertexArray = m_lines[i];
        }

        const float multiplier = lineWidth / 2.0f;

        const sf::Vector2f v1 = multiplier * sf::Vector2f(
            static_cast<float>(cos(p1)), static_cast<float>(sin(p1))
        );

        const sf::Vector2f v2 = multiplier * sf::Vector2f(
            static_cast<float>(cos(p2)), static_cast<float>(sin(p2))
        );

        (*vertexArray)[0].position = vertex + v2;
        (*vertexArray)[1].position = vertex + v1;
        (*vertexArray)[2].position = next + v1;
        (*vertexArray)[3].position = next + v2;

        for (uint8_t i = 0; i < 4; i++)
            (*vertexArray)[i].color = color;

        if (m_lines.size() < m_vertices.size() - 1)
            m_lines.push_back(vertexArray);

        i++;
    }
}

void Path::_computeConnectors(float lineWidth, sf::Color color)
{
    if (m_vertices.size() < 2) return;

    size_t i = 0;
    for (auto it = m_lines.begin(); it < m_lines.end(); it++)
    {
        // 'closed' is true if the end and beginning points are the same, or if m_closed is true.
        bool closed = m_closed;

        sf::VertexArray current, next;

        if ((it + 1) == m_lines.end())
        {
            if (!m_closed)
            {
                auto a = *(m_vertices.begin());
                auto b = *(m_vertices.end() - 1);

                closed = a == b;
            }

            if (!closed) break;

            current = **it;
            next = **m_lines.begin();
        }
        else
        {
            current = **it;
            next = **(it + 1);
        }

        sf::VertexArray* vertexArray;

        size_t bounds = m_lines.size();
        if (!closed) bounds--;

        if (m_connectors.size() < bounds)
        {
            if (m_lineJoin == LineJoin::Miter)
            {
                vertexArray = new sf::VertexArray(sf::Quads, 8);
            }
            else if(m_lineJoin == LineJoin::Bevel)
            {
                vertexArray = new sf::VertexArray(sf::Quads, 4);
            }
            else if (m_lineJoin == LineJoin::Round)
            {
                vertexArray = new sf::VertexArray(sf::TriangleFan, 32);
            }
            else
            {
                vertexArray = nullptr;
            }
        }
        else
        {
            vertexArray = m_connectors[i];
        }

        if (vertexArray == nullptr)
        {
            return;
        }

        if (m_lineJoin == LineJoin::Miter)
        {
            const sf::Vector2f delta1 = current[3].position - current[0].position;
            const double angle1 = atan2(delta1.y, delta1.x);

            const sf::Vector2f delta2 = next[3].position - next[0].position;
            const double angle2 = atan2(delta2.y, delta2.x);

            const sf::Vector2f delta3 = current[2].position - current[1].position;
            const double angle3 = atan2(delta3.y, delta3.x);

            const sf::Vector2f delta4 = next[2].position - next[1].position;
            const double angle4 = atan2(delta4.y, delta4.x);

            auto intersection1 = _pointOfIntersection(angle1, current[3].position, angle2, next[0].position);
            auto intersection2 = _pointOfIntersection(angle3, current[2].position, angle4, next[1].position);

            (*vertexArray)[0] = current[3].position;
            (*vertexArray)[1] = current[2].position;
            (*vertexArray)[2] = intersection1;
            (*vertexArray)[3] = intersection2;

            (*vertexArray)[4] = intersection1;
            (*vertexArray)[5] = intersection2;
            (*vertexArray)[6] = next[1].position;
            (*vertexArray)[7] = next[0].position;
        } 
        else if (m_lineJoin == LineJoin::Bevel)
        {
            (*vertexArray)[0] = current[3].position;
            (*vertexArray)[1] = current[2].position;
            (*vertexArray)[2] = next[0].position;
            (*vertexArray)[3] = next[1].position;
        }
        else if (m_lineJoin == LineJoin::Round)
        {
            const float tau = 4.0f * static_cast<float>(PI_2);
            const float interval = tau / static_cast<float>(vertexArray->getVertexCount());
            const float multiplier = lineWidth / 2.0f;

            float angle = 0;

            (*vertexArray)[0].position = m_vertices.at(i);

            for (uint8_t j = 1; j < vertexArray->getVertexCount(); j++)
            {
                (*vertexArray)[j].position = m_vertices.at(i) + sf::Vector2f(multiplier * sf::Vector2f(
                    static_cast<float>(cos(angle)), static_cast<float>(sin(angle))
                ));
                angle += interval;
            }

            (*vertexArray)[vertexArray->getVertexCount() - 1].position = m_vertices.at(i) + sf::Vector2f(multiplier, 0);
        }

        for (uint8_t i = 0; i < vertexArray->getVertexCount(); i++)
            (*vertexArray)[i].color = color;

        if(m_connectors.size() < bounds)
            m_connectors.push_back(vertexArray);

        i++;
    }
}

void Path::_maybeCompute(float lineWidth, sf::Color color)
{
    if (m_computed) return;

    _computeVertices(lineWidth, color);
    _computeConnectors(lineWidth, color);

    m_computed = true;
}

void Path::draw(float lineWidth, sf::Color color, sf::RenderWindow* window)
{
    m_lineWidth = lineWidth;

    _maybeCompute(lineWidth, color);

    for (auto it = m_lines.begin(); it < m_lines.end(); it++)
        window->draw(**it);

    for (auto it = m_connectors.begin(); it < m_connectors.end(); it++)
        window->draw(**it);
}

bool Path::empty() const
{
    return m_vertices.empty();
}

sf::Vector2f Path::_pointOfIntersection(double a1, sf::Vector2f p1, double a2, sf::Vector2f p2)
{
    const double dy = static_cast<double>(p2.y) - static_cast<double>(p1.y);

    const double m1 = static_cast<float>(tan(a1)),
        m2 = static_cast<float>(tan(a2)),
        h = ((m2 * p2.x - m1 * p1.x) - dy) / (m2 - m1),
        k = m1 * (h - p1.x) + p1.y;

    return sf::Vector2f(static_cast<float>(h), static_cast<float>(k));
}

void Path::lineJoin(LineJoin join)
{
    m_lineJoin = join;
}

LineJoin Path::lineJoin() const
{
    return m_lineJoin;
}
