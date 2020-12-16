#ifndef _CANVAS_EVENT_HPP
#define _CANVAS_EVENT_HPP

namespace Canvas
{
enum class EventType
{
    Unload,
    Resize,
    Keyboard,
    MouseDown,
    MouseUp,
    MouseMove,
    Wheel,
    Focus,
    Blur
};

class Event
{
public:
    Event();
    virtual ~Event();
};

class KeyboardEvent : public Event
{
public:
    KeyboardEvent(const sf::Event::KeyEvent&);
    KeyboardEvent(const sf::Event::KeyEvent&, const sf::Event::TextEvent&);

    ~KeyboardEvent();

    bool altKey() const;
    bool ctrlKey() const;
    bool shiftKey() const;
    bool metaKey() const;

    bool getModifierState(const std::string&) const;

    std::string key() const;
    std::string code() const;

private:
    bool m_altKey, m_ctrlKey, m_shiftKey, m_metaKey;

    std::string m_key, m_code;

    void _setCode(sf::Keyboard::Key);
};

class MouseEvent : public Event
{
public:
    MouseEvent();
    MouseEvent(const sf::Event::MouseButtonEvent&);
    MouseEvent(const sf::Event::MouseMoveEvent&);
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
    WheelEvent(const sf::Event::MouseWheelScrollEvent&);
    ~WheelEvent();

    float deltaX() const;
    float deltaY() const;

private:
    float m_deltaX, m_deltaY;
};
}

#endif