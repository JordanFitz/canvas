#ifndef _CANVAS_CANVAS_HPP
#define _CANVAS_CANVAS_HPP

#include "Context.hpp"

namespace Canvas
{
class Context;

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

    void addEventListener(const std::string&, void (*proc)(const sf::Event&));
    void dispatchEvent(const std::string&, const sf::Event&);

    int initialize();
    void hookUpdate(void (*proc)(Canvas&));
    void hookRender(void (*proc)(Canvas&));

    sf::RenderWindow* window() const;

private:
    sf::RenderWindow* m_window;

    unsigned int m_width, m_height;

    Context m_context;

    std::map<std::string, std::vector<void(*)(const sf::Event&)>> m_handlers;

    void (*m_render)(Canvas&);
    void (*m_update)(Canvas&);
};
}

#endif

