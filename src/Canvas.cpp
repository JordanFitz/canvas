#include <string>

#include <SFML/Graphics.hpp>

#include "CanvasGradient.hpp"
#include "Context.hpp"
#include "Event.hpp"

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

    m_window->setFramerateLimit(60);
    m_window->setVerticalSyncEnabled(true);
}

Canvas::~Canvas()
{
    delete m_window;
}

int Canvas::initialize()
{
    while (m_window->isOpen())
    {
        sf::Event::KeyEvent keyPressedEvent;
        sf::Event::TextEvent textEnteredEvent;

        bool keyPressed = false;
        bool textEntered = false;

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

                sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
                m_window->setPosition(sf::Vector2i(
                    desktop.width / 2 - m_window->getSize().x / 2,
                    desktop.height / 2 - m_window->getSize().y / 2
               ));
            }

            switch (event.type)
            {
            case sf::Event::Closed:
                dispatchEvent("unload", Event());
                break;
            case sf::Event::Resized:
                dispatchEvent("resize", Event());
                break;
            case sf::Event::TextEntered:
                textEntered = true;
                textEnteredEvent = event.text;
                break;
            case sf::Event::KeyPressed:
                keyPressed = true;
                keyPressedEvent = event.key;
                break;
            case sf::Event::KeyReleased:
                //dispatchEvent("keyup", event);
                break;
            case sf::Event::MouseButtonPressed:
                dispatchEvent("mousedown", MouseEvent(event.mouseButton));
                break;
            case sf::Event::MouseButtonReleased:
                dispatchEvent("mouseup", MouseEvent(event.mouseButton));
                break;
            case sf::Event::MouseMoved:
                dispatchEvent("mousemove", MouseEvent(event.mouseMove));
                break;
            case sf::Event::MouseWheelScrolled:
                dispatchEvent("wheel", WheelEvent(event.mouseWheelScroll));
                break;
            case sf::Event::GainedFocus:
                dispatchEvent("focus", Event());
                break;
            case sf::Event::LostFocus:
                dispatchEvent("blur", Event());
                break;
            }
        }

        if (keyPressed && textEntered)
        {
            dispatchEvent("keydown", KeyboardEvent(keyPressedEvent, textEnteredEvent));
        }
        else if(keyPressed)
        {
            dispatchEvent("keydown", KeyboardEvent(keyPressedEvent));
        }
        else if(textEntered)
        {
            printf("ERROR: Got a TextEntered event ('%c') but not a KeyPressed event!\n", textEnteredEvent.unicode);
        }

        // TODO: Handle keyup!

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

void Canvas::addEventListener(const std::string& type, void (*handler)(const Event&))
{
    if (m_handlers.find(type) == m_handlers.end())
    {
        m_handlers.insert(
            std::pair<std::string, std::vector<void (*)(const Event&)>>
            (type, std::vector<void (*)(const Event&)>())
        );
    }

    m_handlers.at(type).push_back(handler);
}

void Canvas::dispatchEvent(const std::string& type, const Event& event)
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