#include <cctype>
#include <map>
#include <string>

#include "Image.hpp"
#include "Path.hpp"
#include "TextMetrics.hpp"
#include "CanvasGradient.hpp"
#include "Util.hpp"
#include "Canvas.hpp"

#include "Context.hpp"

#define CURRENT_PATH m_paths.at(m_pathCount - 1)

namespace Canvas {
sf::Color Context::parseColor(std::string style)
{
    auto result = sf::Color::Black;

    Util::trim(style);

    if (style.length() == 0)
    {
        return result;
    }

    std::transform(style.begin(), style.end(), style.begin(), [](unsigned char c) {
        return std::tolower(c);
    });

    if (style == "lightsalmon") return sf::Color(255, 160, 122);
    if (style == "salmon") return sf::Color(250, 128, 114);
    if (style == "darksalmon") return sf::Color(233, 150, 122);
    if (style == "lightcoral") return sf::Color(240, 128, 128);
    if (style == "indianred") return sf::Color(205, 92, 92);
    if (style == "crimson") return sf::Color(220, 20, 60);
    if (style == "firebrick") return sf::Color(178, 34, 34);
    if (style == "red") return sf::Color(255, 0, 0);
    if (style == "darkred") return sf::Color(139, 0, 0);
    if (style == "coral") return sf::Color(255, 127, 80);
    if (style == "tomato") return sf::Color(255, 99, 71);
    if (style == "orangered") return sf::Color(255, 69, 0);
    if (style == "gold") return sf::Color(255, 215, 0);
    if (style == "orange") return sf::Color(255, 165, 0);
    if (style == "darkorange") return sf::Color(255, 140, 0);
    if (style == "lightyellow") return sf::Color(255, 255, 224);
    if (style == "lemonchiffon") return sf::Color(255, 250, 205);
    if (style == "lightgoldenrodyellow") return sf::Color(250, 250, 210);
    if (style == "papayawhip") return sf::Color(255, 239, 213);
    if (style == "moccasin") return sf::Color(255, 228, 181);
    if (style == "peachpuff") return sf::Color(255, 218, 185);
    if (style == "palegoldenrod") return sf::Color(238, 232, 170);
    if (style == "khaki") return sf::Color(240, 230, 140);
    if (style == "darkkhaki") return sf::Color(189, 183, 107);
    if (style == "yellow") return sf::Color(255, 255, 0);
    if (style == "lawngreen") return sf::Color(124, 252, 0);
    if (style == "chartreuse") return sf::Color(127, 255, 0);
    if (style == "limegreen") return sf::Color(50, 205, 50);
    if (style == "lime") return sf::Color(0, 255, 0);
    if (style == "forestgreen") return sf::Color(34, 139, 34);
    if (style == "green") return sf::Color(0, 128, 0);
    if (style == "darkgreen") return sf::Color(0, 100, 0);
    if (style == "greenyellow") return sf::Color(173, 255, 47);
    if (style == "yellowgreen") return sf::Color(154, 205, 50);
    if (style == "springgreen") return sf::Color(0, 255, 127);
    if (style == "mediumspringgreen") return sf::Color(0, 250, 154);
    if (style == "lightgreen") return sf::Color(144, 238, 144);
    if (style == "palegreen") return sf::Color(152, 251, 152);
    if (style == "darkseagreen") return sf::Color(143, 188, 143);
    if (style == "mediumseagreen") return sf::Color(60, 179, 113);
    if (style == "seagreen") return sf::Color(46, 139, 87);
    if (style == "olive") return sf::Color(128, 128, 0);
    if (style == "darkolivegreen") return sf::Color(85, 107, 47);
    if (style == "olivedrab") return sf::Color(107, 142, 35);
    if (style == "lightcyan") return sf::Color(224, 255, 255);
    if (style == "cyan") return sf::Color(0, 255, 255);
    if (style == "aqua") return sf::Color(0, 255, 255);
    if (style == "aquamarine") return sf::Color(127, 255, 212);
    if (style == "mediumaquamarine") return sf::Color(102, 205, 170);
    if (style == "paleturquoise") return sf::Color(175, 238, 238);
    if (style == "turquoise") return sf::Color(64, 224, 208);
    if (style == "mediumturquoise") return sf::Color(72, 209, 204);
    if (style == "darkturquoise") return sf::Color(0, 206, 209);
    if (style == "lightseagreen") return sf::Color(32, 178, 170);
    if (style == "cadetblue") return sf::Color(95, 158, 160);
    if (style == "darkcyan") return sf::Color(0, 139, 139);
    if (style == "teal") return sf::Color(0, 128, 128);
    if (style == "powderblue") return sf::Color(176, 224, 230);
    if (style == "lightblue") return sf::Color(173, 216, 230);
    if (style == "lightskyblue") return sf::Color(135, 206, 250);
    if (style == "skyblue") return sf::Color(135, 206, 235);
    if (style == "deepskyblue") return sf::Color(0, 191, 255);
    if (style == "lightsteelblue") return sf::Color(176, 196, 222);
    if (style == "dodgerblue") return sf::Color(30, 144, 255);
    if (style == "cornflowerblue") return sf::Color(100, 149, 237);
    if (style == "steelblue") return sf::Color(70, 130, 180);
    if (style == "royalblue") return sf::Color(65, 105, 225);
    if (style == "blue") return sf::Color(0, 0, 255);
    if (style == "mediumblue") return sf::Color(0, 0, 205);
    if (style == "darkblue") return sf::Color(0, 0, 139);
    if (style == "navy") return sf::Color(0, 0, 128);
    if (style == "midnightblue") return sf::Color(25, 25, 112);
    if (style == "mediumslateblue") return sf::Color(123, 104, 238);
    if (style == "slateblue") return sf::Color(106, 90, 205);
    if (style == "darkslateblue") return sf::Color(72, 61, 139);
    if (style == "lavender") return sf::Color(230, 230, 250);
    if (style == "thistle") return sf::Color(216, 191, 216);
    if (style == "plum") return sf::Color(221, 160, 221);
    if (style == "violet") return sf::Color(238, 130, 238);
    if (style == "orchid") return sf::Color(218, 112, 214);
    if (style == "fuchsia") return sf::Color(255, 0, 255);
    if (style == "magenta") return sf::Color(255, 0, 255);
    if (style == "mediumorchid") return sf::Color(186, 85, 211);
    if (style == "mediumpurple") return sf::Color(147, 112, 219);
    if (style == "blueviolet") return sf::Color(138, 43, 226);
    if (style == "darkviolet") return sf::Color(148, 0, 211);
    if (style == "darkorchid") return sf::Color(153, 50, 204);
    if (style == "darkmagenta") return sf::Color(139, 0, 139);
    if (style == "purple") return sf::Color(128, 0, 128);
    if (style == "indigo") return sf::Color(75, 0, 130);
    if (style == "pink") return sf::Color(255, 192, 203);
    if (style == "lightpink") return sf::Color(255, 182, 193);
    if (style == "hotpink") return sf::Color(255, 105, 180);
    if (style == "deeppink") return sf::Color(255, 20, 147);
    if (style == "palevioletred") return sf::Color(219, 112, 147);
    if (style == "mediumvioletred") return sf::Color(199, 21, 133);
    if (style == "white") return sf::Color(255, 255, 255);
    if (style == "snow") return sf::Color(255, 250, 250);
    if (style == "honeydew") return sf::Color(240, 255, 240);
    if (style == "mintcream") return sf::Color(245, 255, 250);
    if (style == "azure") return sf::Color(240, 255, 255);
    if (style == "aliceblue") return sf::Color(240, 248, 255);
    if (style == "ghostwhite") return sf::Color(248, 248, 255);
    if (style == "whitesmoke") return sf::Color(245, 245, 245);
    if (style == "seashell") return sf::Color(255, 245, 238);
    if (style == "beige") return sf::Color(245, 245, 220);
    if (style == "oldlace") return sf::Color(253, 245, 230);
    if (style == "floralwhite") return sf::Color(255, 250, 240);
    if (style == "ivory") return sf::Color(255, 255, 240);
    if (style == "antiquewhite") return sf::Color(250, 235, 215);
    if (style == "linen") return sf::Color(250, 240, 230);
    if (style == "lavenderblush") return sf::Color(255, 240, 245);
    if (style == "mistyrose") return sf::Color(255, 228, 225);
    if (style == "gainsboro") return sf::Color(220, 220, 220);
    if (style == "lightgray") return sf::Color(211, 211, 211);
    if (style == "silver") return sf::Color(192, 192, 192);
    if (style == "darkgray") return sf::Color(169, 169, 169);
    if (style == "gray") return sf::Color(128, 128, 128);
    if (style == "dimgray") return sf::Color(105, 105, 105);
    if (style == "lightslategray") return sf::Color(119, 136, 153);
    if (style == "slategray") return sf::Color(112, 128, 144);
    if (style == "darkslategray") return sf::Color(47, 79, 79);
    if (style == "black") return sf::Color(0, 0, 0);
    if (style == "cornsilk") return sf::Color(255, 248, 220);
    if (style == "blanchedalmond") return sf::Color(255, 235, 205);
    if (style == "bisque") return sf::Color(255, 228, 196);
    if (style == "navajowhite") return sf::Color(255, 222, 173);
    if (style == "wheat") return sf::Color(245, 222, 179);
    if (style == "burlywood") return sf::Color(222, 184, 135);
    if (style == "tan") return sf::Color(210, 180, 140);
    if (style == "rosybrown") return sf::Color(188, 143, 143);
    if (style == "sandybrown") return sf::Color(244, 164, 96);
    if (style == "goldenrod") return sf::Color(218, 165, 32);
    if (style == "peru") return sf::Color(205, 133, 63);
    if (style == "chocolate") return sf::Color(210, 105, 30);
    if (style == "saddlebrown") return sf::Color(139, 69, 19);
    if (style == "sienna") return sf::Color(160, 82, 45);
    if (style == "brown") return sf::Color(165, 42, 42);

    std::string originalStyle = style;

    if (m_colorCache.find(style) != m_colorCache.end())
    {
        return m_colorCache.at(style);
    }

    bool parsed = false;

    if (style[0] == '#')
    {
        if (style.length() == 9 || style.length() == 7 || style.length() == 4)
        {
            style = style.substr(1, 9);
            if (style.length() == 3)
            {
                std::stringstream stream;

                stream << style[0] << style[0];
                stream << style[1] << style[1];
                stream << style[2] << style[2];

                style = stream.str();
            }

            sf::Uint8 components[4] = { 0, 0, 0, 255 };

            for (size_t i = 0; i < style.length(); i += 2)
            {
                std::string part = style.substr(i, 2);
                sf::Uint8 component = static_cast<sf::Uint8>(std::stoul(part, nullptr, 16));
                components[i / 2] = component;
            }

            parsed = true;
            result = sf::Color(
                components[0], components[1], components[2], components[3]
            );
        }
    }
    else if (style.rfind("rgb", 0) == 0)
    {
        size_t startPosition = style.rfind("rgba", 0) == 0 ? 4 : 3;

        style = style.substr(startPosition, style.size());
        Util::trim(style);

        if (style[0] == '(' && style[style.size() - 1] == ')')
        {
            style = style.substr(1, style.size() - 2);

            sf::Uint8 components[] = { 0, 0, 0, 255 };
            std::string part = "";

            uint8_t i = 0;
            for (auto it = style.begin(); it < style.end(); it++)
            {
                if (i == 4)
                {
                    i = 0;
                    part = "";
                    break;
                }

                if (*it != ',')
                {
                    part += *it;
                }
                else
                {
                    Util::trim(part);

                    if (i == 3)
                    {
                        double component = round(std::stod(part) * 255.0f);
                        components[i] = static_cast<sf::Uint8>(component);
                    }
                    else
                    {
                        components[i] = static_cast<sf::Uint8>(std::stoi(part));
                    }

                    part = "";
                    i++;
                }
            }

            if (part.size() > 0)
            {
                Util::trim(part);

                if (i == 3)
                {
                    double component = round(std::stod(part) * 255.0f);
                    components[i] = static_cast<sf::Uint8>(component);
                }
                else
                {
                    components[i] = static_cast<sf::Uint8>(std::stoi(part));
                }
            }

            if (i == 3 || i == 2)
            {
                parsed = true;
                result = sf::Color(
                    components[0], components[1], components[2], components[3]
                );
            }
        }
    }
    if (!parsed)
    {
        fprintf(stderr, "Got an invalid color string: %s\n", originalStyle.c_str());
    }

    printf("Cached color string %s as ", originalStyle.c_str());
    Util::printColor(result, "\n");

    m_colorCache.insert(
        std::pair<std::string, sf::Color>(originalStyle, result)
    );

    return result;
}

sf::Text* Context::_parseFontString(std::string& fontString)
{
    Util::trim(fontString);

    if (m_texts.find(fontString) != m_texts.end())
    {
        return m_texts.at(fontString);
    }

    std::vector<std::string> parts;
    std::string part = "";

    std::string family;

    bool italic = false,
        underlined = false,
        bold = false;

    // default SFML text size
    int size = 30;

    for (auto it = fontString.begin(); it < fontString.end(); it++)
    {
        unsigned char c = *it;

        if (c == ' ')
        {
            Util::trim(part);
            if (part.length() > 0)
            {
                parts.push_back(part);
            }
            part = "";
        }
        else
        {
            part += c;
        }
    }

    if (part.length() > 0)
    {
        Util::trim(part);
        if (part.length() > 0)
        {
            parts.push_back(part);
        }
    }

    bool buildingFamily = false;
    for (auto it = parts.begin(); it < parts.end(); it++)
    {
        std::string part = *it;

        if (buildingFamily)
        {
            if (part.substr(part.length() - 1, 1)[0] == '"')
            {
                buildingFamily = false;
                part = part.substr(0, part.length() - 1);
            }

            family += " " + part;
        }
        else if (part == "italic")
        {
            italic = true;
        }
        else if (part == "bold")
        {
            bold = true;
        }
        // Underlining can't technically be done in the Canvas API because
        // it only allows you to set `font` and not `text-decoration`. I'm 
        // allowing it here for convenience.
        else if (part == "underline" || part == "underlined")
        {
            underlined = true;
        }
        else if (std::isdigit(part[0]))
        {
            if (part.length() > 2 && part.substr(part.length() - 2, 2) == "px")
            {
                part = part.substr(0, part.length() - 2);
                size = std::stoi(part);
            }
        }
        else if (part[0] == '"')
        {
            if (part.substr(part.length() - 1, 1)[0] == '"')
            {
                part = part.substr(0, part.length() - 1);
            }
            else
            {
                buildingFamily = true;
            }

            family = part.substr(1, part.length());
        }
        else
        {
            family = part;
        }
    }

    printf(
        "Parsed font string: '%s' ->\n{\n\tsize=%d\n\tfamily=%s\n\tbold=%s\n\tunderlined=%s\n\titalic=%s\n}\n",
        fontString.c_str(),
        size,
        family.c_str(),
        bold ? "true" : "false",
        underlined ? "true" : "false",
        italic ? "true" : "false"
    );

    if (m_fonts.find(family) != m_fonts.end())
    {
        sf::Text* text = new sf::Text();

        text->setFont(*m_fonts.at(family));
        text->setCharacterSize(size);

        sf::Uint32 style = 0;

        if (bold) style |= sf::Text::Bold;
        if (italic) style |= sf::Text::Italic;
        if (underlined) style |= sf::Text::Underlined;

        if (style != 0)
        {
            text->setStyle(style);
        }

        m_texts.insert(std::pair<std::string, sf::Text*>(fontString, text));

        printf("Cached font string '%s'.\n", fontString.c_str());

        return text;
    }
    else
    {
        printf("No loaded font face with the name '%s'.\n", family.c_str());
    }

    printf("Couldn't construct a Text object from font string '%s'.\n", fontString.c_str());

    return nullptr;
}

Context::Context(Canvas* canvas) :
    m_canvas(canvas),
    m_lineWidth(1.0f),
    m_backgroundColor("white"),
    m_lineJoinString("miter"),
    m_lineJoin(LineJoin::Miter),
    m_lineCapString("butt"),
    m_lineCap(LineCap::Butt),
    m_pathCount(0)
{
    m_rectangle = new sf::RectangleShape();

    fillStyle("black");
    strokeStyle("black");
}

Context::~Context()
{
    printf("dest\n");

    delete m_rectangle;

    for (auto it = m_fonts.begin(); it != m_fonts.end(); it++)
        delete it->second;

    for (auto it = m_texts.begin(); it != m_texts.end(); it++)
        delete it->second;

    for (auto it = m_paths.begin(); it < m_paths.end(); it++)
        delete* it;
}

void Context::loadFont(const std::string& name, const std::string& path)
{
    if (m_fonts.find(name) != m_fonts.end())
    {
        printf("Replacing font '%s'\n", name.c_str());
    }

    sf::Font* font = new sf::Font();
    font->loadFromFile(path);
    m_fonts.insert(std::pair<std::string, sf::Font*>(name, font));
}

void Context::font(const std::string& fontString)
{
    m_fontString = fontString;
    m_text = _parseFontString(m_fontString);
}

const std::string& Context::font() const
{
    return m_fontString;
}

const std::string& Context::fillStyle() const
{
    return m_fillStyleString;
}

void Context::fillStyle(const std::string& newStyle)
{
    m_fillStyleString = newStyle;
    m_fillStyle.type = FillStyle::Type::Color;
    m_fillStyle.color = parseColor(newStyle);
    //m_fillColor = parseColor(m_fillStyle);
}

void Context::fillStyle(const CanvasGradient& gradient)
{
    m_fillStyle.type = FillStyle::Type::Gradient;
    m_fillStyle.gradient = &gradient;
}

const std::string& Context::strokeStyle() const
{
    return m_strokeStyle;
}

void Context::strokeStyle(const std::string& newStyle)
{
    m_strokeStyle = newStyle;
    m_strokeColor = parseColor(m_strokeStyle);
}

void Context::lineWidth(float newWidth)
{
    m_lineWidth = newWidth;
}

float Context::lineWidth() const
{
    return m_lineWidth;
}

void Context::fillRect(float x, float y, float width, float height)
{
    m_rectangle->setSize(sf::Vector2f(width, height));
    m_rectangle->setPosition(sf::Vector2f(x, y));
    m_rectangle->setFillColor(m_fillStyle.color);
    m_rectangle->setOutlineThickness(0.0f);

    if (m_fillStyle.type == FillStyle::Type::Color)
    {
        m_canvas->window()->draw(*m_rectangle);
    }
    else
    {
        m_canvas->window()->draw(*m_rectangle, CanvasGradient::getShader(m_fillStyle.gradient));
    }
}

void Context::strokeRect(float x, float y, float width, float height)
{
    m_rectangle->setSize(sf::Vector2f(width - m_lineWidth, height - m_lineWidth));
    m_rectangle->setPosition(sf::Vector2f(x + m_lineWidth / 2, y + m_lineWidth / 2));
    m_rectangle->setFillColor(sf::Color::Transparent);
    m_rectangle->setOutlineColor(m_strokeColor);
    m_rectangle->setOutlineThickness(m_lineWidth);

    m_canvas->window()->draw(*m_rectangle);
}

void Context::clearRect()
{
    auto color = parseColor(m_backgroundColor);
    m_canvas->window()->clear(color);
}

void Context::clearRect(float x, float y, float width, float height)
{
    auto fs = fillStyle();

    fillStyle(m_backgroundColor.c_str());
    fillRect(x, y, width, height);
    fillStyle(fs);
}

void Context::drawImage(const Image& image, float dx, float dy)
{
    sf::Sprite* sprite = image.getSprite();
    sprite->setPosition(sf::Vector2f(dx, dy));
    m_canvas->window()->draw(*sprite);
}

void Context::drawImage(const Image& image, float dx, float dy, float dWidth, float dHeight)
{
    sf::Sprite* sprite = image.getSprite();

    sprite->setPosition(sf::Vector2f(dx, dy));

    auto size = sprite->getTexture()->getSize();
    sprite->setScale(sf::Vector2f(dWidth / size.x, dHeight / size.y));

    m_canvas->window()->draw(*sprite);
}

void Context::drawImage(const Image& image, float sx, float sy, float sWidth, float sHeight, float dx, float dy, float dWidth, float dHeight)
{
    sf::Sprite* sprite = image.getSprite();

    sf::IntRect rect = sprite->getTextureRect();
    sprite->setTextureRect(sf::IntRect(
        static_cast<int>(sx),
        static_cast<int>(sy),
        static_cast<int>(sWidth),
        static_cast<int>(sHeight)
    ));

    sprite->setPosition(sf::Vector2f(dx, dy));
    sprite->setScale(sf::Vector2f(dWidth / sWidth, dHeight / sHeight));

    m_canvas->window()->draw(*sprite);

    sprite->setTextureRect(rect);
}

void Context::fillText(const std::string& string, float x, float y)
{
    if (m_text == nullptr)
    {
        printf("Call to fillText() with no font set.");
        return;
    }

    m_text->setFillColor(m_fillStyle.color);
    m_text->setOutlineThickness(0.0f);

    m_text->setPosition(sf::Vector2f(x, y));
    m_text->setString(string);

    if (m_fillStyle.type == FillStyle::Type::Color)
    {
        m_canvas->window()->draw(*m_text);
    }
    else
    {
        m_canvas->window()->draw(*m_text, CanvasGradient::getShader(m_fillStyle.gradient));
    }
}

void Context::strokeText(const std::string& string, float x, float y)
{
    if (m_text == nullptr)
    {
        printf("Call to strokeText() with no font set.");
        return;
    }

    m_text->setFillColor(sf::Color::Transparent);
    m_text->setOutlineColor(m_strokeColor);
    m_text->setOutlineThickness(m_lineWidth);

    m_text->setPosition(sf::Vector2f(x, y));
    m_text->setString(string);

    m_canvas->window()->draw(*m_text);
}

TextMetrics Context::measureText(const std::string& string)
{
    m_text->setString(string);
    m_text->setOutlineThickness(0.0f);
    m_text->setFillColor(sf::Color::Transparent);

    m_canvas->window()->draw(*m_text);

    return { m_text->getLocalBounds().width };
}

void Context::beginPath()
{
    m_pathCount = 0;
}

void Context::moveTo(float x, float y)
{
    if (m_pathCount == m_paths.size())
    {
        m_paths.push_back(new Path());
    }

    m_pathCount++;

    CURRENT_PATH->reset();
    CURRENT_PATH->addVertex(x, y);
}

void Context::lineTo(float x, float y)
{
    if (m_pathCount == 0) return;
    CURRENT_PATH->addVertex(x, y);
}

void Context::closePath()
{
    if (m_pathCount == 0) return;
    CURRENT_PATH->close();
}

void Context::stroke()
{
    for (size_t i = 0; i < m_pathCount; i++)
    {
        m_paths.at(i)->stroke(m_lineWidth, m_strokeColor, m_lineJoin, m_lineCap, m_canvas->window());
    }
}

void Context::fill()
{
    for (size_t i = 0; i < m_pathCount; i++)
    {
        m_paths.at(i)->fill(m_fillStyle, m_canvas->window());
    }
}

void Context::backgroundColor(const std::string& style)
{
    m_backgroundColor = style;
}

const std::string& Context::backgroundColor() const
{
    return m_backgroundColor;
}

void Context::lineJoin(const std::string& join)
{
    if (m_lineJoinString == join) return;

    m_lineJoinString = join;

    if (m_lineJoinString == "round")
    {
        m_lineJoin = LineJoin::Round;
    }
    else if (m_lineJoinString == "bevel")
    {
        m_lineJoin = LineJoin::Bevel;
    }
    else
    {
        m_lineJoin = LineJoin::Miter;
    }
}

const std::string& Context::lineJoin() const
{
    return m_lineJoinString;
}

void Context::lineCap(const std::string& cap)
{
    if (m_lineCapString == cap) return;

    m_lineCapString = cap;

    if (m_lineCapString == "square")
    {
        m_lineCap = LineCap::Square;
    }
    else if (m_lineCapString == "round")
    {
        m_lineCap = LineCap::Round;
    }
    else
    {
        m_lineCap = LineCap::Butt;
    }
}

const std::string& Context::lineCap() const
{
    return m_lineCapString;
}

void Context::arc(float x, float y, float radius, float startAngle, float endAngle, bool anticlockwise)
{
    if (m_paths.size() == 0)
        m_paths.push_back(new Path());

    if (m_pathCount == 0) m_pathCount = 1;

    CURRENT_PATH->reset();
    CURRENT_PATH->arc(x, y, radius, startAngle, endAngle, anticlockwise);
}

void Context::rect(float x, float y, float width, float height)
{
    moveTo(x, y);
    lineTo(x + width, y);
    lineTo(x + width, y + height);
    lineTo(x, y + height);
    lineTo(x, y);
}

CanvasGradient Context::createLinearGradient(float x1, float y1, float x2, float y2)
{
    return CanvasGradient(this, x1, y1, x2, y2);
}
}
