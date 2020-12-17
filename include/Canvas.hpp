#ifndef _CANVAS_CANVAS_HPP
#define _CANVAS_CANVAS_HPP

#include <functional>
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

    template <typename F>
    void hookUpdate(F&& proc) { m_render = proc; }

    template <typename F>
    void hookRender(F&& proc) { m_update = proc; }

    void backgroundColor(const std::string&);
    const std::string& backgroundColor() const;

    sf::RenderWindow* _sfWindow() const;

private:
    sf::RenderWindow* m_window;

    unsigned int m_width, m_height;

    Context m_context;

    std::map<std::string, std::vector<void(*)(const Event&)>> m_handlers;

    std::function<void(Canvas&)> m_render;
    std::function<void(Canvas&)> m_update;

    std::string m_backgroundColor;
};
}

#endif
