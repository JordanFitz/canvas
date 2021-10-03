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

// https://stackoverflow.com/a/122721/6238921
//
// Note: This function returns a pointer to a substring of the original string.
// If the given string was allocated dynamically, the caller must not overwrite
// that pointer with the returned value, since the original pointer must be
// deallocated using the same allocator with which it was allocated.  The return
// value must NOT be deallocated using free() etc.
char* trim(char* str)
{
    char* end;

    // Trim leading space
    while (isspace(static_cast<unsigned char>(*str)))
    {
        str++;
    }

    if (*str == 0)  // All spaces?
        return str;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && isspace(static_cast<unsigned char>(*end)))
    {
        end--;
    }

    // Write new null terminator character
    end[1] = '\0';

    return str;
}

/*void toLower(char* str)
{
    size_t length = strlen(str);

    for (size_t i = 0; i < length; i++)
    {
        str[i] = tolower(str[i]);
    }
}*/

bool isAlphabetical(const char* str)
{
    size_t length = strlen(str);

    for (size_t i = 0; i < length; i++)
    {
        if (!isalpha(str[i])) return false;
    }

    return true;
}

uint32_t encodeColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
{
    return (r << 24) | (g << 16) | (b << 8) | a;
}

uint32_t encodeColor(sf::Color color)
{
    return encodeColor(color.r, color.g, color.b, color.a);
}

sf::Color extractColor(uint32_t color)
{
    return sf::Color(
        (color >> 24) & 0xFF,
        (color >> 16) & 0xFF,
        (color >> 8) & 0xFF,
        (color) & 0xFF
    );
}

uint8_t stringToColorComponent(char* str, bool isFloating = false)
{
    char* copy = static_cast<char*>(calloc(strlen(str) + 1, sizeof(char)));
    if (copy)
    {
        memcpy(copy, str, strlen(str) + 1);
    }
    else
    {
        return 0;
    }

    char* trimmed = trim(copy);

    uint8_t result = 0;

    if (!isFloating)
    {
        result = static_cast<uint8_t>(atoi(copy));
    }
    else
    {
        double component = round(std::stod(copy) * 255.0f);
        result = static_cast<uint8_t>(component);
    }   

    free(copy);

    return result;
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
