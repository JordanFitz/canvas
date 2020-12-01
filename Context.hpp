#ifndef _CANVAS_CONTEXT_HPP
#define _CANVAS_CONTEXT_HPP

#include <SFML/Graphics.hpp>

namespace Canvas
{
class Canvas;
class Image;
class Path;
class CanvasGradient;
struct TextMetrics;
enum class LineJoin;
enum class LineCap;

struct FillStyle
{
    enum class Type {
        Gradient,
        Color
    };

    Type type = Type::Color;

    sf::Color color;
    const CanvasGradient* gradient;
};

class Context
{
public:
    Context(Canvas*);
    ~Context();

    void loadFont(const std::string&, const std::string&);

    void fillStyle(const CanvasGradient&);

    void fillStyle(const std::string&);
    const std::string& fillStyle() const;

    void strokeStyle(const std::string&);
    const std::string& strokeStyle() const;

    void lineWidth(float);
    float lineWidth() const;

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

    void font(const std::string&);
    const std::string& font() const;

    void fillText(const std::string&, float, float);
    void strokeText(const std::string&, float, float);

    void beginPath();
    void moveTo(float, float);
    void lineTo(float, float);
    void rect(float, float, float, float);
    void stroke();
    void fill();
    void closePath();

    void arc(float, float, float, float, float, bool anticlockwise = false);

    TextMetrics measureText(const std::string&);
    CanvasGradient createLinearGradient(float, float, float, float);

    sf::Color parseColor(std::string);

private:
    Canvas* m_canvas;

    sf::RectangleShape* m_rectangle;

    std::map<std::string, sf::Color> m_colorCache;
    std::map<std::string, sf::Font*> m_fonts;
    std::map<std::string, sf::Text*> m_texts;

    std::string m_fillStyleString, m_strokeStyle, m_backgroundColor;
    sf::Color m_strokeColor;

    std::string m_lineJoinString, m_lineCapString;

    LineJoin m_lineJoin;
    LineCap m_lineCap;

    FillStyle m_fillStyle;

    float m_lineWidth;

    sf::Text* m_text;
    std::string m_fontString;
    sf::Text* _parseFontString(std::string&);

    std::vector<Path*> m_paths;
    size_t m_pathCount;
};
}

#endif
