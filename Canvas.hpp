#ifndef _CANVAS_HPP
#define _CANVAS_HPP

#include <SFML/Graphics.hpp>

class Image;
class Path;
struct TextMetrics;
enum class LineJoin;
enum class LineCap;

class Canvas
{
public:
    Canvas();
    ~Canvas();

    void loadFont(const std::string&, const std::string&);

    void fillStyle(const std::string&);
    const std::string& fillStyle() const;

    void strokeStyle(const std::string&);
    const std::string& strokeStyle() const;

    void lineWidth(float);
    float lineWidth() const;

    void width(unsigned int);
    unsigned int width() const;

    void height(unsigned int);
    unsigned int height() const;

    void lineJoin(const std::string&);
    const std::string& lineJoin() const;

    void lineCap(const std::string&);
    const std::string& lineCap() const;

    void backgroundColor(const std::string&);
    const std::string& backgroundColor() const;

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

    void addEventListener(const std::string&, void (*proc)(const sf::Event&));
    void dispatchEvent(const std::string&, const sf::Event&);

    void font(const std::string&);
    const std::string& font() const;

    void fillText(const std::string&, float, float);
    void strokeText(const std::string&, float, float);

    void beginPath();
    void moveTo(float, float);
    void lineTo(float, float);
    void stroke();
    void fill();
    void closePath();

    void arc(float, float, float, float, float, bool anticlockwise = false);
    
    TextMetrics measureText(const std::string&);

private:
    sf::RenderWindow* m_window;
    sf::RectangleShape* m_rectangle;

    std::map<std::string, sf::Color> m_colorCache;
    std::map<std::string, sf::Font*> m_fonts;
    std::map<std::string, sf::Text*> m_texts;

    std::string m_fillStyle, m_strokeStyle, m_backgroundColor;
    sf::Color m_fillColor, m_strokeColor;

    std::string m_lineJoinString, m_lineCapString;

    LineJoin m_lineJoin;
    LineCap m_lineCap;

    float m_lineWidth;

    unsigned int m_width, m_height;

    void (*m_render)(Canvas&);
    void (*m_update)(Canvas&);

    std::map<std::string, std::vector<void(*)(const sf::Event&)>> m_handlers;

    sf::Text* m_text;
    std::string m_fontString;
    sf::Text* _parseFontString(std::string&);

    sf::Color _parseColor(std::string);

    std::vector<Path*> m_paths;
    size_t m_pathCount;
};

#endif
