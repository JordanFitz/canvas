#ifndef _PATH_HPP
#define _PATH_HPP

enum class LineJoin
{
    Round,
    Bevel,
    Miter
};

enum class LineCap
{
    Butt,
    Round,
    Square
};

constexpr auto PI_2 = 1.57079632679;
constexpr auto   PI = 3.14159265359;
constexpr auto  TAU = 6.28318530718;

class Path
{
public:
    Path();
    ~Path();

    void arc(float, float, float, float, float, bool);

    void reset();
    void close();
    void addVertex(float, float);

    bool empty() const;

    void draw(float, sf::Color, LineJoin, LineCap, sf::RenderWindow*);

private:
    std::vector<sf::Vector2f> m_vertices;
    std::vector<sf::Vector2f> m_oldVertices;

    std::vector<sf::VertexArray*> m_lines;
    std::vector<sf::VertexArray*> m_connectors;
    std::vector<sf::VertexArray*> m_caps;

    sf::VertexArray* m_lineWithNoThickness;

    bool m_closed;
    bool m_computed;

    void _computeVertices(float, sf::Color);
    void _computeConnectors(float, sf::Color, LineJoin);
    void _computeCaps(float, sf::Color, LineCap);
    void _maybeCompute(float, sf::Color, LineJoin, LineCap);

    sf::Vector2f _pointOfIntersection(double, sf::Vector2f, double, sf::Vector2f);

    void _populateCircle(sf::VertexArray*, sf::Vector2f, float);
};

#endif