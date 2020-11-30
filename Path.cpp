#include <vector>
#include <sstream>
#include <assert.h>

#include <SFML/Graphics.hpp>

#include "earcut.hpp"
#include "Path.hpp"

Path::Path() :
    m_closed(false),
    m_computed(false),
    m_lineWithNoThickness(nullptr)
{
}

Path::~Path()
{
    for (auto it = m_lines.begin(); it < m_lines.end(); it++)
        delete* it;

    for (auto it = m_connectors.begin(); it < m_connectors.end(); it++)
        delete* it;

    for (auto it = m_caps.begin(); it < m_caps.end(); it++)
        delete* it;
    
    delete m_lineWithNoThickness;

    m_vertices.clear();
    m_lines.clear();
    m_connectors.clear();
    m_caps.clear();
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

    m_vertices.push_back(m_vertices.front());
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
            vertexArray = m_lines.at(i);
        }

        const float multiplier = lineWidth / 2.0f;

        const auto v1 = multiplier * sf::Vector2f(
            static_cast<float>(cos(p1)), static_cast<float>(sin(p1))
        );

        const auto v2 = multiplier * sf::Vector2f(
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

void Path::_computeConnectors(float lineWidth, sf::Color color, LineJoin joinType)
{
    if (m_vertices.size() < 2) return;

    size_t i = 0;
    for (auto it = m_lines.begin(); it < m_lines.end(); it++)
    {
        sf::VertexArray current, next;

        if ((it + 1) == m_lines.end())
        {
            if (!m_closed) break;

            current = **it;
            next = **m_lines.begin();
        }
        else
        {
            current = **it;
            next = **(it + 1);
        }

        sf::VertexArray* vertexArray;

        size_t connectorCount = m_lines.size();
        if (!m_closed) connectorCount--;

        if (m_connectors.size() < connectorCount)
        {
            if (joinType == LineJoin::Miter)
            {
                vertexArray = new sf::VertexArray(sf::Quads, 8);
            }
            else if(joinType == LineJoin::Bevel)
            {
                vertexArray = new sf::VertexArray(sf::Quads, 4);
            }
            else if (joinType == LineJoin::Round)
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
            vertexArray = m_connectors.at(i);

            if (joinType == LineJoin::Miter)
            {
                vertexArray->setPrimitiveType(sf::Quads);
                vertexArray->resize(8);
            }
            else if (joinType == LineJoin::Bevel)
            {
                vertexArray->setPrimitiveType(sf::Quads);
                vertexArray->resize(4);
            }
            else if (joinType == LineJoin::Round)
            {
                vertexArray->setPrimitiveType(sf::TriangleFan);
                vertexArray->resize(32);
            }
        }

        if (vertexArray == nullptr)
        {
            return;
        }

        if (joinType == LineJoin::Miter)
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
            (*vertexArray)[2] = intersection2;
            (*vertexArray)[3] = intersection1;

            (*vertexArray)[4] = intersection1;
            (*vertexArray)[5] = intersection2;
            (*vertexArray)[6] = next[1].position;
            (*vertexArray)[7] = next[0].position;
        } 
        else if (joinType == LineJoin::Bevel)
        {
            (*vertexArray)[0] = current[2].position;
            (*vertexArray)[1] = current[3].position;
            (*vertexArray)[2] = next[0].position;
            (*vertexArray)[3] = next[1].position;
        }
        else if (joinType == LineJoin::Round)
        {
            _populateCircle(vertexArray, m_vertices.at(i+1), lineWidth / 2.0f);
        }

        for (uint8_t i = 0; i < vertexArray->getVertexCount(); i++)
            (*vertexArray)[i].color = color;

        if(m_connectors.size() < connectorCount)
            m_connectors.push_back(vertexArray);

        i++;
    }
}

void Path::_computeCaps(float lineWidth, sf::Color color, LineCap capType)
{
    if (m_closed || m_vertices.size() < 2) return;

    /*for (auto it = m_caps.begin(); it < m_caps.end(); it++)
        delete* it;
    m_caps.clear();*/

    sf::VertexArray* cap1 = nullptr;
    sf::VertexArray* cap2 = nullptr;

    sf::Vector2f firstVertex = *(m_vertices.begin());
    sf::Vector2f lastVertex = *(m_vertices.end() - 1);

    sf::VertexArray* firstLine = m_lines.at(0);
    sf::VertexArray* lastLine = m_lines.at(m_vertices.size() - 2);

    const float multiplier = lineWidth / 2.0f;

    if (capType == LineCap::Round)
    {
        if (m_caps.size() == 0)
        {
            cap1 = new sf::VertexArray();
            cap2 = new sf::VertexArray();
        }
        else
        {
            cap1 = m_caps.at(0);
            cap2 = m_caps.at(1);
        }

        cap1->setPrimitiveType(sf::TriangleFan);
        cap1->resize(32);

        cap2->setPrimitiveType(sf::TriangleFan);
        cap2->resize(32);

        _populateCircle(cap1, firstVertex, multiplier);
        _populateCircle(cap2, lastVertex, multiplier);
    }
    else if(capType == LineCap::Square)
    {
        if (m_caps.size() == 0)
        {
            cap1 = new sf::VertexArray();
            cap2 = new sf::VertexArray();
        }
        else
        {
            cap1 = m_caps.at(0);
            cap2 = m_caps.at(1);
        }

        cap1->setPrimitiveType(sf::Quads);
        cap1->resize(4);

        cap2->setPrimitiveType(sf::Quads);
        cap2->resize(4);

        const auto delta1 = (*firstLine)[0].position - (*firstLine)[3].position;
        const auto delta2 = (*lastLine)[0].position - (*lastLine)[3].position;
        const float angle1 = atan2(delta1.y, delta1.x);
        const float angle2 = atan2(delta2.y, delta2.x);

        const auto v1 = multiplier * sf::Vector2f(
            static_cast<float>(cos(angle1)), static_cast<float>(sin(angle1))
        );
        const auto v2 = multiplier * sf::Vector2f(
            static_cast<float>(cos(angle2)), static_cast<float>(sin(angle2))
        );

        (*cap1)[0].position = (*firstLine)[0].position + v1;
        (*cap1)[1].position = (*firstLine)[1].position + v1;
        (*cap1)[2].position = (*firstLine)[1].position;
        (*cap1)[3].position = (*firstLine)[0].position;

        (*cap2)[0].position = (*lastLine)[3].position;
        (*cap2)[1].position = (*lastLine)[2].position;
        (*cap2)[2].position = (*lastLine)[2].position - v2;
        (*cap2)[3].position = (*lastLine)[3].position - v2;
    }
    if (cap1 != nullptr && cap2 != nullptr)
    {
        if (m_caps.size() == 0)
        {
            m_caps.push_back(cap1);
            m_caps.push_back(cap2);
        }

        for (size_t i = 0; i < cap1->getVertexCount(); i++)
            (*cap1)[i].color = color;

        for (size_t i = 0; i < cap2->getVertexCount(); i++)
            (*cap2)[i].color = color;
    }
}

void Path::_maybeCompute(float lineWidth, sf::Color color, LineJoin join, LineCap cap)
{
    if (m_computed || m_oldVertices == m_vertices) return;

    _computeVertices(lineWidth, color);
    _computeConnectors(lineWidth, color, join);
    _computeCaps(lineWidth, color, cap);

    m_computed = true;
}

void Path::stroke(float lineWidth, sf::Color color, LineJoin join, LineCap cap, sf::RenderWindow* window)
{
    if (lineWidth > 1.0f)
    {
        _maybeCompute(lineWidth, color, join, cap);

        for (size_t i = 0; i < m_vertices.size() - 1; i++)
            window->draw(*m_lines.at(i));

        for (size_t i = 0; i < m_vertices.size() - (m_closed ? 1 : 2); i++)
            window->draw(*m_connectors.at(i));

        if (!m_closed && m_caps.size() == 2)
        {
            window->draw(*m_caps.at(0));
            window->draw(*m_caps.at(1));
        }
    }
    else if(lineWidth <= 1.0f)
    {
        if (m_lineWithNoThickness == nullptr)
            m_lineWithNoThickness = new sf::VertexArray(sf::LinesStrip, m_vertices.size());

        if (m_lineWithNoThickness->getVertexCount() != m_vertices.size())
            m_lineWithNoThickness->resize(m_vertices.size());

        for (size_t i = 0; i < m_vertices.size(); i++)
        {
            (*m_lineWithNoThickness)[i].position = m_vertices.at(i);
            (*m_lineWithNoThickness)[i].color = color;
        }

        window->draw(*m_lineWithNoThickness);
    }

    m_oldVertices = m_vertices;
}

void Path::fill(sf::Color color, sf::RenderWindow* window)
{
    std::vector<std::vector<sf::Vector2f>> polygon = { m_vertices };
    std::vector<uint32_t> indices = mapbox::earcut<uint32_t>(polygon);
    sf::VertexArray vertices(sf::Triangles);

    for (auto& it : indices)
    {
        auto v = sf::Vertex(m_vertices.at(it), color);
        vertices.append(v);
    }

    window->draw(vertices);
}

bool Path::empty() const
{
    return m_vertices.empty();
}

sf::Vector2f Path::_pointOfIntersection(double a1, sf::Vector2f p1, double a2, sf::Vector2f p2)
{
    const double dy = static_cast<double>(p2.y) - static_cast<double>(p1.y);

    const double m1 = tan(a1),
        m2 = tan(a2),
        h = ((m2 * p2.x - m1 * p1.x) - dy) / (m2 - m1),
        k = m1 * (h - p1.x) + p1.y;

    return sf::Vector2f(static_cast<float>(h), static_cast<float>(k));
}

void Path::_populateCircle(sf::VertexArray* vertexArray, sf::Vector2f center, float radius)
{
    const float interval = static_cast<float>(TAU) / static_cast<float>(vertexArray->getVertexCount());

    float angle = 0;

    (*vertexArray)[0].position = center;

    for (uint8_t i = 1; i < vertexArray->getVertexCount(); i++)
    {
        const auto offset = radius * sf::Vector2f(
            static_cast<float>(cos(angle)), static_cast<float>(sin(angle))
        );

        (*vertexArray)[i].position = center + offset;

        angle += interval;
    }

    (*vertexArray)[vertexArray->getVertexCount() - 1].position = center + sf::Vector2f(radius, 0);
}

void Path::arc(float x, float y, float radius, float startAngle, float endAngle, bool anticlockwise)
{
    if (m_closed) return;

    const sf::Vector2f center(x, y);
    const float interval = 0.1f;
    const float extra = 0.001f;

    if (anticlockwise)
    {
        const float d = endAngle - startAngle;
        startAngle += d;
        endAngle += static_cast<float>(TAU) - d;

        if (startAngle == endAngle)
            startAngle = 0;
    }

    // HACK: Adding an extra vertex to make the edges look square?
    m_vertices.push_back(center + radius * sf::Vector2f(
        static_cast<float>(cos(startAngle - extra)),
        static_cast<float>(sin(startAngle - extra))
    ));

    for (float angle = startAngle; angle < endAngle; angle += interval)
    {
        const sf::Vector2f v = radius * sf::Vector2f(
            static_cast<float>(cos(angle)),
            static_cast<float>(sin(angle))
        );

        m_vertices.push_back(center + v);
    }    

    m_vertices.push_back(center + radius * sf::Vector2f(
        static_cast<float>(cos(endAngle)),
        static_cast<float>(sin(endAngle))
    ));

    // HACK: See above
    m_vertices.push_back(center + radius * sf::Vector2f(
        static_cast<float>(cos(endAngle + extra)),
        static_cast<float>(sin(endAngle + extra))
    ));

    return;
}
