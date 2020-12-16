#include <SFML/Graphics.hpp>

#include "Event.hpp"

#define sfK sf::Keyboard
#define sfM sf::Mouse::Button

namespace Canvas
{
Event::Event() {}

//Event::Event(EventType type) : m_type(type)
//{}

//Event::Event(const sf::Event& rawEvent, EventType type)
//    : m_rawEvent(rawEvent), m_type(type)
//{}

Event::~Event()
{}

KeyboardEvent::KeyboardEvent(const sf::Event::KeyEvent& rawEvent) :
    m_altKey(rawEvent.alt),
    m_shiftKey(rawEvent.shift),
    m_ctrlKey(rawEvent.control),
    m_metaKey(rawEvent.system),
    m_key("Unidentified")
{
    switch (rawEvent.code)
    {
    case sfK::RShift:
    case sfK::LShift: m_key = "Shift"; break;

    case sfK::RAlt:
    case sfK::LAlt: m_key = "Alt"; break;

    case sfK::RControl:
    case sfK::LControl: m_key = "Control"; break;

    case sfK::RSystem:
    case sfK::LSystem: m_key = "Meta"; break;

    case sfK::Insert: m_key = "Insert"; break;
    case sfK::Home: m_key = "Home"; break;
    case sfK::PageUp: m_key = "PageUp"; break;
    case sfK::Delete: m_key = "Delete"; break;
    case sfK::End: m_key = "End"; break;
    case sfK::PageDown: m_key = "PageDown"; break;

    case sfK::Down: m_key = "ArrowDown"; break;
    case sfK::Left: m_key = "ArrowLeft"; break;
    case sfK::Right: m_key = "ArrowRight"; break;
    case sfK::Up: m_key = "ArrowUp"; break;

    case sfK::Pause: m_key = "Pause"; break;

    case sfK::F1: m_key = "F1"; break;
    case sfK::F2: m_key = "F2"; break;
    case sfK::F3: m_key = "F3"; break;
    case sfK::F4: m_key = "F4"; break;
    case sfK::F5: m_key = "F5"; break;
    case sfK::F6: m_key = "F6"; break;
    case sfK::F7: m_key = "F7"; break;
    case sfK::F8: m_key = "F8"; break;
    case sfK::F9: m_key = "F9"; break;
    case sfK::F10: m_key = "F10"; break;
    case sfK::F11: m_key = "F11"; break;
    case sfK::F12: m_key = "F12"; break;
    case sfK::F13: m_key = "F13"; break;
    case sfK::F14: m_key = "F14"; break;
    case sfK::F15: m_key = "F15"; break;

    case sfK::Unknown: break;

    default: printf("Unidentified key code: %d\n", rawEvent.code); break;
    }
}

KeyboardEvent::KeyboardEvent(const sf::Event::KeyEvent& keyEvent, const sf::Event::TextEvent& textEvent) :
    m_altKey(keyEvent.alt),
    m_shiftKey(keyEvent.shift),
    m_ctrlKey(keyEvent.control),
    m_metaKey(keyEvent.system),
    m_key(1, textEvent.unicode)
{
    switch (keyEvent.code)
    {
    case sfK::Enter: m_key = "Enter"; break;
    case sfK::Tab: m_key = "Tab"; break;
    case sfK::Escape: m_key = "Escape"; break;
    case sfK::Backspace: m_key = "Backspace"; break;

    default: break;
    }
}

KeyboardEvent::~KeyboardEvent()
{}

bool KeyboardEvent::altKey() const { return m_altKey; }
bool KeyboardEvent::ctrlKey() const { return m_ctrlKey; }
bool KeyboardEvent::shiftKey() const { return m_shiftKey; }
bool KeyboardEvent::metaKey() const { return m_metaKey; }

std::string KeyboardEvent::key() const { return m_key; }

uint8_t MouseEvent::_getButton(sfM button)
{
    switch (button)
    {
    case sfM::Left: return 0;
    case sfM::Middle: return 1;
    case sfM::Right: return 2;
    case sfM::XButton1: return 3;
    case sfM::XButton2: return 4;
    }

    return 0;
}

MouseEvent::MouseEvent() : m_buttons(0), m_button(0)
{
    m_altKey =
        sfK::isKeyPressed(sfK::LAlt) ||
        sfK::isKeyPressed(sfK::RAlt);

    m_shiftKey =
        sfK::isKeyPressed(sfK::LShift) ||
        sfK::isKeyPressed(sfK::RShift);

    m_ctrlKey =
        sfK::isKeyPressed(sfK::LControl) ||
        sfK::isKeyPressed(sfK::RControl);

    m_metaKey =
        sfK::isKeyPressed(sfK::LSystem) ||
        sfK::isKeyPressed(sfK::RSystem);

    for (int i = sfM::Left; i < sfM::ButtonCount; i++)
    {
        auto button = static_cast<sfM>(i);
        if (sf::Mouse::isButtonPressed(button))
            m_buttons += 1 << _getButton(button);
    }

    sf::Vector2i screenPosition = sf::Mouse::getPosition();
    m_screenX = screenPosition.x;
    m_screenY = screenPosition.y;
}

MouseEvent::MouseEvent(const sf::Event::MouseButtonEvent& rawEvent):
    MouseEvent()
{
    m_button = _getButton(rawEvent.button);
    m_clientX = rawEvent.x;
    m_clientY = rawEvent.y;
}

MouseEvent::MouseEvent(const sf::Event::MouseMoveEvent& rawEvent) :
    MouseEvent()
{
    m_clientX = rawEvent.x;
    m_clientY = rawEvent.y;
}

MouseEvent::~MouseEvent() {}

uint8_t MouseEvent::button() const { return m_button; }
uint8_t MouseEvent::buttons() const { return m_buttons; }

int MouseEvent::clientX() const { return m_clientX; }
int MouseEvent::clientY() const { return m_clientY; }
int MouseEvent::screenX() const { return m_screenX; }
int MouseEvent::screenY() const { return m_screenY; }

bool MouseEvent::altKey() const { return m_altKey; }
bool MouseEvent::ctrlKey() const { return m_ctrlKey; }
bool MouseEvent::shiftKey() const { return m_shiftKey; }
bool MouseEvent::metaKey() const { return m_metaKey; }

WheelEvent::WheelEvent(const sf::Event::MouseWheelScrollEvent& rawEvent)
{
    if (rawEvent.wheel == sf::Mouse::HorizontalWheel)
    {
        m_deltaX = rawEvent.delta;
        m_deltaY = 0;
    }
    else
    {
        m_deltaX = 0;
        m_deltaY = rawEvent.delta;
    }
}

WheelEvent::~WheelEvent() {}

float WheelEvent::deltaX() const { return m_deltaX; }
float WheelEvent::deltaY() const { return m_deltaY; }
}