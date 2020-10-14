#include "Canvas.hpp"
#include "util.hpp"

sf::Color Canvas::_parseStyle(std::string& style)
{
    auto defaultColor = sf::Color::Black;

    trim(style);

    if (style.length() == 0)
    {
        return defaultColor;
    }

    if (style[0] == '#')
    {
        if (style.length() == 9 || style.length() == 7 || style.length() == 4)
        {
            style = style.substr(1, 9);
            if (style.length() == 3)
            {
                style = style + style;
            }

            sf::Uint8 color[4] = { 0, 0, 0, 255 };

            for (uint8_t i = 0; i < style.length(); i += 2)
            {
                std::string part = style.substr(i, 2);
                sf::Uint8 component = static_cast<sf::Uint8>(std::stoul(part, nullptr, 16));
                color[i / 2] = component;
            }

            return sf::Color(
                color[0], color[1], color[2], color[3]
            );
        }
        else
        {
            return defaultColor;
        }
    }

    return defaultColor;
}

Canvas::Canvas() :
    m_width(300),
    m_height(150),
    m_lineWidth(1.0f),
    m_render(nullptr),
    m_update(nullptr)
{
    sf::RectangleShape m_rect(sf::Vector2f(0, 0));
    m_window = new sf::RenderWindow(
        sf::VideoMode(m_width, m_height),
        "Canvas", sf::Style::Close
    );
}

Canvas::~Canvas()
{
}

void Canvas::hookUpdate(void (*proc)(Canvas*))
{
    m_update = proc;
}

void Canvas::hookRender(void (*proc)(Canvas*))
{
    m_render = proc;
}

void Canvas::initialize()
{
    while (m_window->isOpen())
    {
        sf::Event event;
        while (m_window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                m_window->close();
            }
            if (event.type == sf::Event::Resized)
            {
                sf::FloatRect visibleArea(
                    0, 0,
                    static_cast<float>(event.size.width),
                    static_cast<float>(event.size.height)
                );
                m_window->setView(sf::View(visibleArea));
            }
        }

        m_window->clear();

        if(m_update != nullptr) m_update(this);
        if(m_render != nullptr) m_render(this);

        m_window->display();
    }
}

std::string Canvas::fillStyle()
{
    return m_fillStyle;
}

void Canvas::fillStyle(const char* newStyle)
{
    m_fillStyle = std::string(newStyle);
    m_fillColor = _parseStyle(m_fillStyle);
}

std::string Canvas::strokeStyle()
{
    return m_strokeStyle;
}

void Canvas::strokeStyle(const char* newStyle)
{
    m_strokeStyle = std::string(newStyle);
}

void Canvas::lineWidth(float newWidth)
{
    m_lineWidth = newWidth;
}

float Canvas::lineWidth()
{
    return m_lineWidth;
}

void Canvas::width(unsigned int newWidth)
{
    m_width = newWidth;
    sf::Vector2u size = m_window->getSize();
    m_window->setSize(sf::Vector2u(m_width, size.y));
}

unsigned int Canvas::width()
{
    return m_width;
}

void Canvas::height(unsigned int newHeight)
{
    m_height = newHeight;
    sf::Vector2u size = m_window->getSize();
    m_window->setSize(sf::Vector2u(size.x, m_height));
}

unsigned int Canvas::height()
{
    return m_height;
}

void Canvas::fillRect(float x, float y, float width, float height)
{
    // TODO: Not sure if instantiating a new rect every call is the most efficient?
    sf::RectangleShape rect(sf::Vector2f(width, height));
    rect.setPosition(sf::Vector2f(x, y));
    rect.setFillColor(m_fillColor);
    rect.setOutlineThickness(0.0f);
    m_window->draw(rect);
}
