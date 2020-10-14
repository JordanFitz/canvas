#pragma once

#include <SFML/Graphics.hpp>

class Canvas
{
public:
    Canvas();
    ~Canvas();

    void fillStyle(const char*);
    std::string fillStyle();

    void strokeStyle(const char*);
    std::string strokeStyle();

    void lineWidth(float);
    float lineWidth();

    void width(unsigned int);
    unsigned int width();

    void height(unsigned int);
    unsigned int height();

    void fillRect(float, float, float, float);

    void initialize();
    void hookUpdate(void (*proc)(Canvas*));
    void hookRender(void (*proc)(Canvas*));

private:
    sf::RenderWindow* m_window;

    std::string m_fillStyle, m_strokeStyle;
    sf::Color m_fillColor;

    float m_lineWidth;

    unsigned int m_width, m_height;

    void (*m_render)(Canvas*) = nullptr;
    void (*m_update)(Canvas*) = nullptr;

    sf::Color _parseStyle(std::string&);
};

