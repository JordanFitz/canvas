#ifndef _CANVAS_CANVAS_HPP
#define _CANVAS_CANVAS_HPP

#include "Context.hpp"
#include "Event.hpp"

namespace Canvas
{
template <typename T> 
static inline const T& eventAs(const Event& event)
{
    return dynamic_cast<const T&>(event);
}

class Context;
class Event;

class Canvas
{
public:
    Canvas();
    ~Canvas();

    Context& getContext(const std::string&);
    Context& getContext();

    void width(unsigned int);
    unsigned int width() const;

    void height(unsigned int);
    unsigned int height() const;

    void addEventListener(const std::string&, void (*proc)(const Event&));
    void dispatchEvent(const std::string&, const Event&);

    int initialize();
    void hookUpdate(void (*proc)(Canvas&));
    void hookRender(void (*proc)(Canvas&));

    void backgroundColor(const std::string&);
    const std::string& backgroundColor() const;

    sf::RenderWindow* window() const;

private:
    sf::RenderWindow* m_window;

    unsigned int m_width, m_height;

    Context m_context;

    std::map<std::string, std::vector<void(*)(const Event&)>> m_handlers;

    void (*m_render)(Canvas&);
    void (*m_update)(Canvas&);

    std::string m_backgroundColor;
};
}

#endif
