#include <SFML/Graphics.hpp>

#include "Event.hpp"

#define sfK sf::Keyboard
#define sfM sf::Mouse::Button

namespace Canvas
{
Event::Event(EventType type, const std::string& name) : m_type(type), m_name(name)
{}

//Event::Event(const sf::Event& rawEvent, EventType type)
//    : m_rawEvent(rawEvent), m_type(type)
//{}

Event::~Event()
{}

EventType Event::type() const
{
    return m_type;
}

std::string Event::name() const
{
    return m_name;
}

void Event::name(const std::string& value)
{
    m_name = value;
}

KeyboardEvent::KeyboardEvent(const std::string& name, const sf::Event::KeyEvent& keyEvent) :
    Event(EventType::Keyboard, name),
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

    //default: printf("Unidentified key code: %d\n", keyEvent.code); break;
    }

    _setCode(keyEvent.code);
}

KeyboardEvent::KeyboardEvent(const std::string& name, const sf::Event::KeyEvent& keyEvent, const sf::Event::TextEvent& textEvent) :
    Event(EventType::Keyboard, name),
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

sfK::Key KeyboardEvent::codeToKey(const std::string& code)
{
    if (code == "KeyA") return sfK::A;
    if (code == "KeyB") return sfK::B;
    if (code == "KeyC") return sfK::C;
    if (code == "KeyD") return sfK::D;
    if (code == "KeyE") return sfK::E;
    if (code == "KeyF") return sfK::F;
    if (code == "KeyG") return sfK::G;
    if (code == "KeyH") return sfK::H;
    if (code == "KeyI") return sfK::I;
    if (code == "KeyJ") return sfK::J;
    if (code == "KeyK") return sfK::K;
    if (code == "KeyL") return sfK::L;
    if (code == "KeyM") return sfK::M;
    if (code == "KeyN") return sfK::N;
    if (code == "KeyO") return sfK::O;
    if (code == "KeyP") return sfK::P;
    if (code == "KeyQ") return sfK::Q;
    if (code == "KeyR") return sfK::R;
    if (code == "KeyS") return sfK::S;
    if (code == "KeyT") return sfK::T;
    if (code == "KeyU") return sfK::U;
    if (code == "KeyV") return sfK::V;
    if (code == "KeyW") return sfK::W;
    if (code == "KeyX") return sfK::X;
    if (code == "KeyY") return sfK::Y;
    if (code == "KeyZ") return sfK::Z;

    if (code == "Digit0") return sfK::Num0;
    if (code == "Digit1") return sfK::Num1;
    if (code == "Digit2") return sfK::Num2;
    if (code == "Digit3") return sfK::Num3;
    if (code == "Digit4") return sfK::Num4;
    if (code == "Digit5") return sfK::Num5;
    if (code == "Digit6") return sfK::Num6;
    if (code == "Digit7") return sfK::Num7;
    if (code == "Digit8") return sfK::Num8;
    if (code == "Digit9") return sfK::Num9;

    if (code == "F1") return sfK::F1;
    if (code == "F2") return sfK::F2;
    if (code == "F3") return sfK::F3;
    if (code == "F4") return sfK::F4;
    if (code == "F5") return sfK::F5;
    if (code == "F6") return sfK::F6;
    if (code == "F7") return sfK::F7;
    if (code == "F8") return sfK::F8;
    if (code == "F9") return sfK::F9;
    if (code == "F10") return sfK::F10;
    if (code == "F11") return sfK::F11;
    if (code == "F12") return sfK::F12;
    if (code == "F13") return sfK::F13;
    if (code == "F14") return sfK::F14;
    if (code == "F15") return sfK::F15;

    if (code == "Escape") return sfK::Escape;
    if (code == "ShiftLeft") return sfK::LShift;
    if (code == "ShiftRight") return sfK::RShift;
    if (code == "ControlLeft") return sfK::LControl;
    if (code == "ControlRight") return sfK::RControl;
    if (code == "AltLeft") return sfK::LAlt;
    if (code == "AltRight") return sfK::RAlt;
    if (code == "MetaLeft") return sfK::LSystem;
    if (code == "MetaRight") return sfK::RSystem;
    if (code == "ContextMenu") return sfK::Menu;
    if (code == "BracketLeft") return sfK::LBracket;
    if (code == "BracketRight") return sfK::RBracket;
    if (code == "Semicolon") return sfK::Semicolon;
    if (code == "Comma") return sfK::Comma;
    if (code == "Period") return sfK::Period;
    if (code == "Quote") return sfK::Quote;
    if (code == "Slash") return sfK::Slash;
    if (code == "Backslash") return sfK::Backslash;
    if (code == "Backquote") return sfK::Tilde;
    if (code == "Equal") return sfK::Equal;
    if (code == "Minus") return sfK::Hyphen;
    if (code == "Space") return sfK::Space;
    if (code == "Enter") return sfK::Enter;
    if (code == "Backspace") return sfK::Backspace;
    if (code == "Tab") return sfK::Tab;
    if (code == "PageUp") return sfK::PageUp;
    if (code == "PageDown") return sfK::PageDown;
    if (code == "End") return sfK::End;
    if (code == "Home") return sfK::Home;
    if (code == "Insert") return sfK::Insert;
    if (code == "Delete") return sfK::Delete;
    if (code == "NumpadAdd") return sfK::Add;
    if (code == "NumpadSubtract") return sfK::Subtract;
    if (code == "NumpadMultiply") return sfK::Multiply;
    if (code == "NumpadDivide") return sfK::Divide;
    if (code == "ArrowLeft") return sfK::Left;
    if (code == "ArrowRight") return sfK::Right;
    if (code == "ArrowUp") return sfK::Up;
    if (code == "ArrowDown") return sfK::Down;
    if (code == "Pause") return sfK::Pause;

    if (code == "Numpad0") return sfK::Numpad0;
    if (code == "Numpad1") return sfK::Numpad1;
    if (code == "Numpad2") return sfK::Numpad2;
    if (code == "Numpad3") return sfK::Numpad3;
    if (code == "Numpad4") return sfK::Numpad4;
    if (code == "Numpad5") return sfK::Numpad5;
    if (code == "Numpad6") return sfK::Numpad6;
    if (code == "Numpad7") return sfK::Numpad7;
    if (code == "Numpad8") return sfK::Numpad8;
    if (code == "Numpad9") return sfK::Numpad9;

    return sfK::Unknown;
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

MouseEvent::MouseEvent(const std::string& name) :
    Event(EventType::Mouse, name),
    m_buttons(0),
    m_button(0),
    m_clientX(0),
    m_clientY(0)
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

MouseEvent::MouseEvent(const std::string& name, const sf::Event::MouseButtonEvent& rawEvent):
    MouseEvent(name)
{
    m_button = _getButton(rawEvent.button);
    m_clientX = rawEvent.x;
    m_clientY = rawEvent.y;
}

MouseEvent::MouseEvent(const std::string& name, const sf::Event::MouseMoveEvent& rawEvent) :
    MouseEvent(name)
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

WheelEvent::WheelEvent(const std::string& name, const sf::Event::MouseWheelScrollEvent& rawEvent) : Event(EventType::Wheel, name)
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