#pragma once

constexpr auto PI_2 = 1.57079632679;

class Path
{
public:
    Path();
    ~Path();

    void reset();
    void close();
    void addVertex(float, float);

    bool empty() const;

    void draw(float, sf::Color, sf::RenderWindow*);

private:
    std::vector<sf::Vector2f> m_vertices;
    std::vector<sf::VertexArray*> m_lines;
    std::vector<sf::VertexArray*> m_connectors;

    std::vector<sf::Vector2f> m_projections;

    bool m_closed;
    bool m_computed;

    float m_lineWidth;

    void _computeVertices(float, sf::Color);
    void _computeConnectors(sf::Color);
    void _maybeCompute(float, sf::Color);

    sf::Vector2f _pointOfIntersection(double, sf::Vector2f, double, sf::Vector2f);
};

