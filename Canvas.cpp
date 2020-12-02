#include <string>

#include <SFML/Graphics.hpp>

#include "CanvasGradient.hpp"
#include "Context.hpp"

#include "Canvas.hpp"

namespace Canvas
{
Canvas::Canvas() :
    m_width(300),
    m_height(150),
    m_update(nullptr),
    m_render(nullptr),
    m_context(this),
    m_backgroundColor("white")
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    m_window = new sf::RenderWindow(
        sf::VideoMode(m_width, m_height),
        "Canvas", sf::Style::Close, settings
    );
}

Canvas::~Canvas()
{
    delete m_window;
}

int Canvas::initialize()
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

                CanvasGradient::setHeight(static_cast<float>(event.size.height));
            }

            switch (event.type)
            {
            case sf::Event::Closed:
                dispatchEvent("unload", event);
                break;
            case sf::Event::Resized:
                dispatchEvent("resize", event);
                break;
            case sf::Event::KeyPressed:
                dispatchEvent("keypress", event);
                break;
            case sf::Event::KeyReleased:
                dispatchEvent("keyup", event);
                break;
            case sf::Event::MouseButtonPressed:
                dispatchEvent("mousedown", event);
                break;
            case sf::Event::MouseButtonReleased:
                dispatchEvent("mouseup", event);
                break;
            case sf::Event::MouseMoved:
                dispatchEvent("mousemove", event);
                break;
            case sf::Event::MouseWheelScrolled:
                dispatchEvent("wheel", event);
                break;
            case sf::Event::GainedFocus:
                dispatchEvent("focus", event);
                break;
            case sf::Event::LostFocus:
                dispatchEvent("blur", event);
                break;
            }
        }

        if (m_update != nullptr) m_update(*this);
        if (m_render != nullptr) m_render(*this);

        m_window->display();
    }

    return 0;
}

Context& Canvas::getContext(const std::string&)
{
    return getContext();
}

Context& Canvas::getContext()
{
    return m_context;
}

sf::RenderWindow* Canvas::window() const
{
    return m_window;
}

void Canvas::width(unsigned int newWidth)
{
    m_width = newWidth;
    sf::Vector2u size = m_window->getSize();
    m_window->setSize(sf::Vector2u(m_width, size.y));
}

unsigned int Canvas::width() const
{
    return m_width;
}

void Canvas::height(unsigned int newHeight)
{
    m_height = newHeight;
    sf::Vector2u size = m_window->getSize();
    m_window->setSize(sf::Vector2u(size.x, m_height));
}

unsigned int Canvas::height() const
{
    return m_height;
}

void Canvas::hookUpdate(void (*proc)(Canvas&))
{
    m_update = proc;
}

void Canvas::hookRender(void (*proc)(Canvas&))
{
    m_render = proc;
}

void Canvas::addEventListener(const std::string& type, void (*handler)(const sf::Event&))
{
    if (m_handlers.find(type) == m_handlers.end())
    {
        m_handlers.insert(
            std::pair<std::string, std::vector<void (*)(const sf::Event&)>>
            (type, std::vector<void (*)(const sf::Event&)>())
        );
    }

    m_handlers.at(type).push_back(handler);
}

void Canvas::dispatchEvent(const std::string& type, const sf::Event& event)
{
    if (m_handlers.find(type) == m_handlers.end())
    {
        return;
    }

    auto handlers = m_handlers.at(type);
    for (auto it = handlers.begin(); it < handlers.end(); it++)
    {
        auto handler = *it;
        handler(event);
    }
}

void Canvas::backgroundColor(const std::string& style)
{
    m_backgroundColor = style;
}

const std::string& Canvas::backgroundColor() const
{
    return m_backgroundColor;
}
}