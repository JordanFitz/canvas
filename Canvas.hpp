#pragma once

#include <SFML/Graphics.hpp>

class Image;

class Canvas
{
public:
    Canvas();
    ~Canvas();

    void fillStyle(const char*);
    std::string fillStyle() const;

    void strokeStyle(const char*);
    std::string strokeStyle() const;

    void lineWidth(float);
    float lineWidth() const;

    void width(unsigned int);
    unsigned int width() const;

    void height(unsigned int);
    unsigned int height() const;

    void fillRect(float, float, float, float);
    void strokeRect(float, float, float, float);

    void drawImage(const Image&, float, float);
    void drawImage(const Image&, float, float, float, float);
    void drawImage(const Image&, float, float, float, float, float, float, float, float);

    void initialize();
    void hookUpdate(void (*proc)(Canvas*));
    void hookRender(void (*proc)(Canvas*));

private:
    sf::RenderWindow* m_window;
    sf::RectangleShape* m_rectangle;

    std::map<std::string, sf::Color> m_colorCache;

    std::string m_fillStyle, m_strokeStyle;
    sf::Color m_fillColor, m_strokeColor;

    float m_lineWidth;

    unsigned int m_width, m_height;

    void (*m_render)(Canvas*) = nullptr;
    void (*m_update)(Canvas*) = nullptr;

    sf::Color _parseColor(std::string&);
    void _registerColor(const char*, const sf::Color&);
};

