#ifndef _CANVAS_EVENT_HPP
#define _CANVAS_EVENT_HPP

#include <SFML\Graphics.hpp>

namespace Canvas
{
enum class EventType
{
    Generic,
    Keyboard,
    Mouse,
    Wheel
};

class Event
{
public:
    Event(EventType, const std::string&);
    virtual ~Event();

    EventType type() const;

    std::string name() const;
    void name(const std::string&);

protected:
    EventType m_type;
    std::string m_name;
};

class KeyboardEvent : public Event
{
public:
    KeyboardEvent(const std::string&, const sf::Event::KeyEvent&);
    KeyboardEvent(const std::string&, const sf::Event::KeyEvent&, const sf::Event::TextEvent&);

    ~KeyboardEvent();

    bool altKey() const;
    bool ctrlKey() const;
    bool shiftKey() const;
    bool metaKey() const;

    bool getModifierState(const std::string&) const;

    std::string key() const;
    std::string code() const;

    static sf::Keyboard::Key codeToKey(const std::string&);

private:
    bool m_altKey, m_ctrlKey, m_shiftKey, m_metaKey;

    std::string m_key, m_code;

    void _setCode(sf::Keyboard::Key);
};

class MouseEvent : public Event
{
public:
    MouseEvent(const std::string&);
    MouseEvent(const std::string&, const sf::Event::MouseButtonEvent&);
    MouseEvent(const std::string&, const sf::Event::MouseMoveEvent&);
    ~MouseEvent();

    uint8_t button() const;
    uint8_t buttons() const;

    int clientX() const;
    int clientY() const;
    int screenX() const;
    int screenY() const;

    bool altKey() const;
    bool ctrlKey() const;
    bool shiftKey() const;
    bool metaKey() const;

private:
    uint8_t m_button, m_buttons;
    int m_clientX, m_clientY, m_screenX, m_screenY;
    bool m_altKey, m_ctrlKey, m_shiftKey, m_metaKey;

    static uint8_t _getButton(sf::Mouse::Button);
};

class WheelEvent : public Event
{
public:
    WheelEvent(const std::string&, const sf::Event::MouseWheelScrollEvent&);
    ~WheelEvent();

    float deltaX() const;
    float deltaY() const;

private:
    float m_deltaX, m_deltaY;
};
}

#endif