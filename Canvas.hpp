#pragma once

#include <SFML/Graphics.hpp>

class Image;
class Path;
struct TextMetrics;
enum class LineJoin;

class Canvas
{
public:
    Canvas();
    ~Canvas();

    void loadFont(const char*, const char*);

    void fillStyle(const char*);
    const char* fillStyle() const;

    void strokeStyle(const char*);
    const char* strokeStyle() const;

    void lineWidth(float);
    float lineWidth() const;

    void width(unsigned int);
    unsigned int width() const;

    void height(unsigned int);
    unsigned int height() const;

    void lineJoin(const char*);
    const char* lineJoin() const;

    void backgroundColor(const char*);
    const char* backgroundColor() const;

    void clearRect();
    void clearRect(float, float, float, float);

    void fillRect(float, float, float, float);
    void strokeRect(float, float, float, float);

    void drawImage(const Image&, float, float);
    void drawImage(const Image&, float, float, float, float);
    void drawImage(const Image&, float, float, float, float, float, float, float, float);

    void initialize();
    void hookUpdate(void (*proc)(Canvas&));
    void hookRender(void (*proc)(Canvas&));

    void addEventListener(const char*, void (*proc)(const sf::Event&));
    void dispatchEvent(const char*, const sf::Event&);

    void font(const char*);
    const char* font() const;

    void fillText(const char*, float, float);
    void strokeText(const char*, float, float);

    void beginPath();
    void moveTo(float, float);
    void lineTo(float, float);
    void stroke();
    void closePath();
    
    TextMetrics measureText(const char*);

private:
    sf::RenderWindow* m_window;
    sf::RectangleShape* m_rectangle;

    std::map<std::string, sf::Color> m_colorCache;
    std::map<std::string, sf::Font*> m_fonts;
    std::map<std::string, sf::Text*> m_texts;

    std::string m_fillStyle, m_strokeStyle, m_backgroundColor;
    sf::Color m_fillColor, m_strokeColor;

    std::string m_lineJoinString;
    LineJoin m_lineJoin;

    float m_lineWidth;

    unsigned int m_width, m_height;

    void (*m_render)(Canvas&) = nullptr;
    void (*m_update)(Canvas&) = nullptr;

    std::map<std::string, std::vector<void(*)(const sf::Event&)>> m_handlers;

    sf::Text* m_text;
    std::string m_fontString;
    sf::Text* _parseFontString(std::string&);

    sf::Color _parseColor(std::string&);
    void _registerColor(const char*, const sf::Color&);

    std::vector<Path*> m_paths;
    Path* m_currentPath = nullptr;
};

