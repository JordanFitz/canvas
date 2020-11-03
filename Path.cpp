#include <vector>
#include <sstream>

#include <SFML/Graphics.hpp>

#include "Path.hpp"

Path::Path() :
    m_closed(false),
    m_computed(false),
    m_lineWidth(-1)
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

        const float c1 = static_cast<float>(cos(p1)),
            s1 = static_cast<float>(sin(p1)),
            c2 = static_cast<float>(cos(p2)),
            s2 = static_cast<float>(sin(p2));

        const float multiplier = lineWidth / 2.0f;

        (*vertexArray)[0].position = sf::Vector2f(
            vertex.x + (multiplier * c2),
            vertex.y + (multiplier * s2)
        );

        (*vertexArray)[1].position = sf::Vector2f(
            vertex.x + (multiplier * c1),
            vertex.y + (multiplier * s1)
        );

        (*vertexArray)[2].position = sf::Vector2f(
            next.x + (multiplier * c1),
            next.y + (multiplier * s1)
        );

        (*vertexArray)[3].position = sf::Vector2f(
            next.x + (multiplier * c2),
            next.y + (multiplier * s2)
        );

        for (uint8_t i = 0; i < 4; i++)
            (*vertexArray)[i].color = color;

        if (m_lines.size() < m_vertices.size() - 1)
            m_lines.push_back(vertexArray);

        i++;
    }
}

void Path::_computeConnectors(sf::Color color)
{
    if (m_vertices.size() < 2) return;

    size_t i = 0;
    for (auto it = m_lines.begin(); it < m_lines.end(); it++)
    {
        // 'closed' is true if the end and beginning points are the same.
        // it isn't affected by m_closed
        bool closed = false;

        sf::VertexArray current, next;

        if ((it + 1) == m_lines.end())
        {
            auto a = *(m_vertices.begin());
            auto b = *(m_vertices.end() - 1);

            closed = a == b;

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
            vertexArray = new sf::VertexArray(sf::Quads, 4);
        }
        else
        {
            vertexArray = m_connectors[i];
        }

        (*vertexArray)[0].position = current[3].position;
        (*vertexArray)[1].position = current[2].position;
        (*vertexArray)[2].position = next[1].position;
        (*vertexArray)[3].position = next[0].position;

        for (uint8_t i = 0; i < 4; i++)
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
    _computeConnectors(color);

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
