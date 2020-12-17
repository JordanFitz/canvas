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

    void loadFont(const std::string&, const std::string&);

    void width(unsigned int);
    unsigned int width() const;

    void height(unsigned int);
    unsigned int height() const;

    void maxFramerate(unsigned int);
    unsigned int maxFramerate() const;

    void vsync(bool);
    bool vsync() const;

    // This is defined in the header because of the template?
    template <typename F>
    void addEventListener(const std::string& name, F&& proc)
    {
        if (m_handlers.find(name) == m_handlers.end())
        {
            m_handlers.insert(std::make_pair(name, std::vector<std::function<void(const Event&)>>()));
        }

        m_handlers.at(name).push_back(proc);
    }

    void dispatchEvent(const std::string&, const Event&);

    int initialize();

    template <typename F>
    void hookUpdate(F&& proc) { m_update = proc; }

    template <typename F>
    void hookRender(F&& proc) { m_render = proc; }

    void backgroundColor(const std::string&);
    const std::string& backgroundColor() const;

    sf::RenderWindow* _sfWindow() const;

    sf::Font* _getFont(const std::string&);

private:
    sf::RenderWindow* m_window;

    unsigned int m_width, m_height, m_maxFramerate;
    bool m_useVsync;

    Context m_context;

    std::map<std::string, sf::Font*> m_fonts;
    std::map<std::string, std::vector<std::function<void(const Event&)>>> m_handlers;

    std::function<void(Canvas&)> m_render;
    std::function<void(Canvas&, float)> m_update;

    std::string m_backgroundColor;
};
}

#endif
