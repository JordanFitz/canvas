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

KeyboardEvent::KeyboardEvent(const sf::Event::KeyEvent& keyEvent) :
    m_altKey(keyEvent.alt),
    m_shiftKey(keyEvent.shift),
    m_ctrlKey(keyEvent.control),
    m_metaKey(keyEvent.system),
    m_key("Unidentified")
{
    switch (keyEvent.code)
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

    default: printf("Unidentified key code: %d\n", keyEvent.code); break;
    }

    _setCode(keyEvent.code);
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

    _setCode(keyEvent.code);
}

KeyboardEvent::~KeyboardEvent()
{}

bool KeyboardEvent::altKey() const { return m_altKey; }
bool KeyboardEvent::ctrlKey() const { return m_ctrlKey; }
bool KeyboardEvent::shiftKey() const { return m_shiftKey; }
bool KeyboardEvent::metaKey() const { return m_metaKey; }

std::string KeyboardEvent::key() const { return m_key; }
std::string KeyboardEvent::code() const { return m_code; }

bool KeyboardEvent::getModifierState(const std::string& keyArg) const
{
    if (keyArg == "Alt")
        return m_altKey;

    if (keyArg == "Control")
        return m_ctrlKey;

    if (keyArg == "Shift")
        return m_shiftKey;

    if (keyArg == "Meta")
        return m_metaKey;

    return false;
}

void KeyboardEvent::_setCode(sf::Keyboard::Key code)
{
    switch (code)
    {
    case sfK::A: m_code = "KeyA"; break;
    case sfK::B: m_code = "KeyB"; break;
    case sfK::C: m_code = "KeyC"; break;
    case sfK::D: m_code = "KeyD"; break;
    case sfK::E: m_code = "KeyE"; break;
    case sfK::F: m_code = "KeyF"; break;
    case sfK::G: m_code = "KeyG"; break;
    case sfK::H: m_code = "KeyH"; break;
    case sfK::I: m_code = "KeyI"; break;
    case sfK::J: m_code = "KeyJ"; break;
    case sfK::K: m_code = "KeyK"; break;
    case sfK::L: m_code = "KeyL"; break;
    case sfK::M: m_code = "KeyM"; break;
    case sfK::N: m_code = "KeyN"; break;
    case sfK::O: m_code = "KeyO"; break;
    case sfK::P: m_code = "KeyP"; break;
    case sfK::Q: m_code = "KeyQ"; break;
    case sfK::R: m_code = "KeyR"; break;
    case sfK::S: m_code = "KeyS"; break;
    case sfK::T: m_code = "KeyT"; break;
    case sfK::U: m_code = "KeyU"; break;
    case sfK::V: m_code = "KeyV"; break;
    case sfK::W: m_code = "KeyW"; break;
    case sfK::X: m_code = "KeyX"; break;
    case sfK::Y: m_code = "KeyY"; break;
    case sfK::Z: m_code = "KeyZ"; break;

    case sfK::Num0: m_code = "Digit0"; break;
    case sfK::Num1: m_code = "Digit1"; break;
    case sfK::Num2: m_code = "Digit2"; break;
    case sfK::Num3: m_code = "Digit3"; break;
    case sfK::Num4: m_code = "Digit4"; break;
    case sfK::Num5: m_code = "Digit5"; break;
    case sfK::Num6: m_code = "Digit6"; break;
    case sfK::Num7: m_code = "Digit7"; break;
    case sfK::Num8: m_code = "Digit8"; break;
    case sfK::Num9: m_code = "Digit9"; break;

    case sfK::F1: m_code = "F1"; break;
    case sfK::F2: m_code = "F2"; break;
    case sfK::F3: m_code = "F3"; break;
    case sfK::F4: m_code = "F4"; break;
    case sfK::F5: m_code = "F5"; break;
    case sfK::F6: m_code = "F6"; break;
    case sfK::F7: m_code = "F7"; break;
    case sfK::F8: m_code = "F8"; break;
    case sfK::F9: m_code = "F9"; break;
    case sfK::F10: m_code = "F10"; break;
    case sfK::F11: m_code = "F11"; break;
    case sfK::F12: m_code = "F12"; break;
    case sfK::F13: m_code = "F13"; break;
    case sfK::F14: m_code = "F14"; break;
    case sfK::F15: m_code = "F15"; break;

    case sfK::Escape: m_code = "Escape"; break;
    case sfK::LShift: m_code = "ShiftLeft"; break;
    case sfK::RShift: m_code = "ShiftRight"; break;
    case sfK::LControl: m_code = "ControlLeft"; break;
    case sfK::RControl: m_code = "ControlRight"; break;
    case sfK::LAlt: m_code = "AltLeft"; break;
    case sfK::RAlt: m_code = "AltRight"; break;
    case sfK::LSystem: m_code = "MetaLeft"; break;
    case sfK::RSystem: m_code = "MetaRight"; break;
    case sfK::Menu: m_code = "ContextMenu"; break;
    case sfK::LBracket: m_code = "BracketLeft"; break;
    case sfK::RBracket: m_code = "BracketRight"; break;
    case sfK::Semicolon: m_code = "Semicolon"; break;
    case sfK::Comma: m_code = "Comma"; break;
    case sfK::Period: m_code = "Period"; break;
    case sfK::Quote: m_code = "Quote"; break;
    case sfK::Slash: m_code = "Slash"; break;
    case sfK::Backslash: m_code = "Backslash"; break;
    case sfK::Tilde: m_code = "Backquote"; break;
    case sfK::Equal: m_code = "Equal"; break;
    case sfK::Hyphen: m_code = "Minus"; break;
    case sfK::Space: m_code = "Space"; break;
    case sfK::Enter: m_code = "Enter"; break;
    case sfK::Backspace: m_code = "Backspace"; break;
    case sfK::Tab: m_code = "Tab"; break;
    case sfK::PageUp: m_code = "PageUp"; break;
    case sfK::PageDown: m_code = "PageDown"; break;
    case sfK::End: m_code = "End"; break;
    case sfK::Home: m_code = "Home"; break;
    case sfK::Insert: m_code = "Insert"; break;
    case sfK::Delete: m_code = "Delete"; break;
    case sfK::Add: m_code = "NumpadAdd"; break;
    case sfK::Subtract: m_code = "NumpadSubtract"; break;
    case sfK::Multiply: m_code = "NumpadMultiply"; break;
    case sfK::Divide: m_code = "NumpadDivide"; break;
    case sfK::Left: m_code = "ArrowLeft"; break;
    case sfK::Right: m_code = "ArrowRight"; break;
    case sfK::Up: m_code = "ArrowUp"; break;
    case sfK::Down: m_code = "ArrowDown"; break;
    case sfK::Pause: m_code = "Pause"; break;

    case sfK::Numpad0: m_code = "Numpad0"; break;
    case sfK::Numpad1: m_code = "Numpad1"; break;
    case sfK::Numpad2: m_code = "Numpad2"; break;
    case sfK::Numpad3: m_code = "Numpad3"; break;
    case sfK::Numpad4: m_code = "Numpad4"; break;
    case sfK::Numpad5: m_code = "Numpad5"; break;
    case sfK::Numpad6: m_code = "Numpad6"; break;
    case sfK::Numpad7: m_code = "Numpad7"; break;
    case sfK::Numpad8: m_code = "Numpad8"; break;
    case sfK::Numpad9: m_code = "Numpad9"; break;

    default: m_code = "Unidentified";
    }
}

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