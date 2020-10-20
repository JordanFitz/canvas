#pragma once

#include <string>
#include <sstream>

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
