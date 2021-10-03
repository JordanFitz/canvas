#include <string>
#include <unordered_map>
#include <functional>

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
    m_backgroundColor("white"),
    m_maxFramerate(0),
    m_useVsync(false),
    m_title("Canvas")
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    m_window = new sf::RenderWindow(
        sf::VideoMode(m_width, m_height),
        m_title, sf::Style::Close, settings
    );
}

Canvas::~Canvas()
{
    delete m_window;

    for (auto it = m_fonts.begin(); it != m_fonts.end(); it++)
        delete it->second;
}

void Canvas::viewPosition(float x, float y)
{
    sf::Vector2f windowSize = sf::Vector2f(m_window->getSize());
    sf::View view = m_window->getView();
    sf::FloatRect viewport = view.getViewport();

    view.setViewport(
        sf::FloatRect(
            x / windowSize.x,
            y / windowSize.y,
            viewport.width,
            viewport.height
        )
    );

    m_window->setView(view);
}

sf::Vector2f Canvas::viewPosition() const
{
    sf::Vector2f windowSize = sf::Vector2f(m_window->getSize());
    sf::View view = m_window->getView();
    sf::FloatRect viewport = view.getViewport();

    return sf::Vector2f(
        viewport.left * windowSize.x,
        viewport.top * windowSize.y
    );
}

void Canvas::close() const
{
    m_window->close();
}

void Canvas::title(const std::string& title)
{
    m_title = title;
    m_window->setTitle(m_title);
}

const std::string& Canvas::title() const
{
    return m_title;
}

void Canvas::loadFont(const std::string& name, const std::string& path)
{
    if (m_fonts.find(name) != m_fonts.end())
    {
        printf("Replacing font '%s'\n", name.c_str());
    }

    sf::Font* font = new sf::Font();
    font->loadFromFile(path);
    m_fonts.insert(std::pair<std::string, sf::Font*>(name, font));
}

sf::Font* Canvas::_getFont(const std::string& name)
{
    if (m_fonts.find(name) != m_fonts.end())
    {
        return m_fonts.at(name);
    }

    return nullptr;
}

int Canvas::initialize()
{
    std::unordered_map<sf::Keyboard::Key, KeyboardEvent> keysBuffer;

    sf::Clock deltaClock;
    float delta = 0.0f;

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
                dispatchEvent("unload", Event(EventType::Generic, "unload")); break;

            case sf::Event::Resized:
                dispatchEvent("resize", Event(EventType::Generic, "resize")); break;

            case sf::Event::TextEntered:
                textEntered = true;
                textEnteredEvent = event.text;
                break;

            case sf::Event::KeyPressed:
                keyPressed = true;
                keyPressedEvent = event.key;
                break;

            case sf::Event::KeyReleased:
                
                // NOTE: This implementation functions differently than a DOM keyup. 
                //       In a browser, you can press Shift+A and get something like 
                //       'Shift' down then 'A' down, then release [shift], and get 
                //       'Shift' up, then release [A] and get 'a' up. In this 
                //       implementation, the keyup event will have the same modifier(s)
                //       as the last keydown event for that key. I'm not sure how else
                //       this could be done without implementing crazy key interpretation
                //       algorithms to generate the correct `key` string value. 
                if (keysBuffer.find(event.key.code) != keysBuffer.end())
                {
                    auto& keyboardEvent = keysBuffer.at(event.key.code);
                    keyboardEvent.name("keyup");
                    dispatchEvent("keyup", keyboardEvent);
                    keysBuffer.erase(event.key.code);
                }

                break;
            case sf::Event::MouseButtonPressed:
                dispatchEvent("mousedown", MouseEvent("mousedown", event.mouseButton));
                break;

            case sf::Event::MouseButtonReleased:
                dispatchEvent("mouseup", MouseEvent("mouseup", event.mouseButton));
                break;

            case sf::Event::MouseMoved:
                dispatchEvent("mousemove", MouseEvent("mousemove", event.mouseMove));
                break;

            case sf::Event::MouseWheelScrolled:
                dispatchEvent("wheel", WheelEvent("wheel", event.mouseWheelScroll));
                break;

            case sf::Event::GainedFocus:
                dispatchEvent("focus", Event(EventType::Generic, "focus")); break;

            case sf::Event::LostFocus:
                dispatchEvent("blur", Event(EventType::Generic, "blur")); break;
            }
        }

        if (keyPressed && textEntered)
        {
            auto event = KeyboardEvent("keydown", keyPressedEvent, textEnteredEvent);
            keysBuffer.insert(std::make_pair(keyPressedEvent.code, event));
            dispatchEvent("keydown", event);
        }
        else if(keyPressed)
        {
            auto event = KeyboardEvent("keydown", keyPressedEvent);
            keysBuffer.insert(std::make_pair(keyPressedEvent.code, event));
            dispatchEvent("keydown", event);
        }
        else if(textEntered)
        {
            printf("ERROR: Got a TextEntered event ('%c') but not a KeyPressed event!\n", textEnteredEvent.unicode);
        }

        if (m_update != nullptr) m_update(*this, delta);
        if (m_render != nullptr) m_render(*this);

        m_window->display();

        delta = deltaClock.restart().asSeconds();
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

sf::RenderWindow* Canvas::_sfWindow() const
{
    return m_window;
}

void Canvas::maxFramerate(unsigned int framerate)
{
    m_maxFramerate = framerate;
    m_window->setFramerateLimit(m_maxFramerate);
}

unsigned int Canvas::maxFramerate() const
{
    return m_maxFramerate;
}

void Canvas::vsync(bool value)
{
    m_useVsync = value;
    m_window->setVerticalSyncEnabled(m_useVsync);
}

bool Canvas::vsync() const
{
    return m_useVsync;
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

//void Canvas::addEventListener(const std::string& type, void (*handler)(const Event&))

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

bool Canvas::_isKeyDown(const sf::Keyboard::Key& key) const
{
    return sf::Keyboard::isKeyPressed(key);
}

}