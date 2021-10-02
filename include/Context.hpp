#ifndef _CANVAS_CONTEXT_HPP
#define _CANVAS_CONTEXT_HPP

#include <SFML/Graphics.hpp>
#include "CanvasGradient.hpp"

namespace Canvas
{
class Canvas;
class Image;
class Path;
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

struct StringCompare
{
    bool operator()(char* a, char* b) const
    {
        return strcmp(a, b) < 0;
    }
};

class Context
{
public:
    Context(Canvas*);
    ~Context();

    void fillStyle(const CanvasGradient&);

    void fillStyle(const char*);
    const char* fillStyle() const;

    void strokeStyle(const char*);
    const char* strokeStyle() const;

    void lineWidth(float);
    float lineWidth() const;

    void lineJoin(const std::string&);
    const std::string& lineJoin() const;

    void lineCap(const std::string&);
    const std::string& lineCap() const;

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

    sf::Color _parseColor(const char*);
    void _cacheDefaultColors();
    void _cacheColor(const char*, uint32_t);

private:
    Canvas* m_canvas;

    sf::RectangleShape* m_rectangle;

    std::map<char*, uint32_t, StringCompare> m_colorCache;
    std::map<std::string, sf::Text*> m_texts;

    char* m_fillStyleString;
    char* m_strokeStyle;

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
