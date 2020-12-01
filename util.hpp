#ifndef _CANVAS_UTIL_HPP
#define _CANVAS_UTIL_HPP

#include <string>
#include <sstream>

namespace Canvas {
namespace Util {
static inline void ltrim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

static inline void rtrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

static inline void trim(std::string& s) {
    ltrim(s);
    rtrim(s);
}

void printColor(const sf::Color& color, const char* suffix = "")
{
    printf("rgba(%d, %d, %d, %.2f)%s", color.r, color.g, color.b, static_cast<float>(color.a) / 255.0f, suffix);
}

void printLine(sf::Vector2f a, sf::Vector2f b, sf::VertexArray v)
{
    printf("(%.2f,%.2f) -> (%.2f,%.2f) {\n", a.x, a.y, b.x, b.y);
    for (uint8_t i = 0; i < v.getVertexCount(); i++)
    {
        printf("ctx.fillRect(%.2f,%.2f,10,10);\n", v[i].position.x, v[i].position.y);
    }
    printf("}\n");
}

void printLine(sf::VertexArray v)
{
    printf("{\n");
    for (uint8_t i = 0; i < v.getVertexCount(); i++)
    {
        printf("ctx.fillRect(%.2f,%.2f,10,10);\n", v[i].position.x, v[i].position.y);
    }
    printf("}\n");
}
}
}

#endif
