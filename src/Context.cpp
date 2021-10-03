#define _USE_MATH_DEFINES

#include <cctype>
#include <map>
#include <string>

#include "Image.hpp"
#include "Path.hpp"
#include "TextMetrics.hpp"
#include "Util.hpp"
#include "Canvas.hpp"

#include "Context.hpp"

#define CURRENT_PATH m_paths.at(m_pathCount - 1)

namespace Canvas {
void Context::_cacheColor(const char* name, uint32_t value)
{
    char* allocated = static_cast<char*>(calloc(strlen(name) + 1, sizeof(char)));
    if (allocated)
    {
        memcpy(allocated, name, strlen(name) + 1);
        char* trimmed = Util::trim(allocated);
        m_colorCache.insert(std::make_pair(trimmed, value));
    }
}

void Context::_cacheDefaultColors()
{
    _cacheColor("lightsalmon", Util::encodeColor(255, 160, 122));
    _cacheColor("salmon", Util::encodeColor(250, 128, 114));
    _cacheColor("darksalmon", Util::encodeColor(233, 150, 122));
    _cacheColor("lightcoral", Util::encodeColor(240, 128, 128));
    _cacheColor("indianred", Util::encodeColor(205, 92, 92));
    _cacheColor("crimson", Util::encodeColor(220, 20, 60));
    _cacheColor("firebrick", Util::encodeColor(178, 34, 34));
    _cacheColor("red", Util::encodeColor(255, 0, 0));
    _cacheColor("darkred", Util::encodeColor(139, 0, 0));
    _cacheColor("coral", Util::encodeColor(255, 127, 80));
    _cacheColor("tomato", Util::encodeColor(255, 99, 71));
    _cacheColor("orangered", Util::encodeColor(255, 69, 0));
    _cacheColor("gold", Util::encodeColor(255, 215, 0));
    _cacheColor("orange", Util::encodeColor(255, 165, 0));
    _cacheColor("darkorange", Util::encodeColor(255, 140, 0));
    _cacheColor("lightyellow", Util::encodeColor(255, 255, 224));
    _cacheColor("lemonchiffon", Util::encodeColor(255, 250, 205));
    _cacheColor("lightgoldenrodyellow", Util::encodeColor(250, 250, 210));
    _cacheColor("papayawhip", Util::encodeColor(255, 239, 213));
    _cacheColor("moccasin", Util::encodeColor(255, 228, 181));
    _cacheColor("peachpuff", Util::encodeColor(255, 218, 185));
    _cacheColor("palegoldenrod", Util::encodeColor(238, 232, 170));
    _cacheColor("khaki", Util::encodeColor(240, 230, 140));
    _cacheColor("darkkhaki", Util::encodeColor(189, 183, 107));
    _cacheColor("yellow", Util::encodeColor(255, 255, 0));
    _cacheColor("lawngreen", Util::encodeColor(124, 252, 0));
    _cacheColor("chartreuse", Util::encodeColor(127, 255, 0));
    _cacheColor("limegreen", Util::encodeColor(50, 205, 50));
    _cacheColor("lime", Util::encodeColor(0, 255, 0));
    _cacheColor("forestgreen", Util::encodeColor(34, 139, 34));
    _cacheColor("green", Util::encodeColor(0, 128, 0));
    _cacheColor("darkgreen", Util::encodeColor(0, 100, 0));
    _cacheColor("greenyellow", Util::encodeColor(173, 255, 47));
    _cacheColor("yellowgreen", Util::encodeColor(154, 205, 50));
    _cacheColor("springgreen", Util::encodeColor(0, 255, 127));
    _cacheColor("mediumspringgreen", Util::encodeColor(0, 250, 154));
    _cacheColor("lightgreen", Util::encodeColor(144, 238, 144));
    _cacheColor("palegreen", Util::encodeColor(152, 251, 152));
    _cacheColor("darkseagreen", Util::encodeColor(143, 188, 143));
    _cacheColor("mediumseagreen", Util::encodeColor(60, 179, 113));
    _cacheColor("seagreen", Util::encodeColor(46, 139, 87));
    _cacheColor("olive", Util::encodeColor(128, 128, 0));
    _cacheColor("darkolivegreen", Util::encodeColor(85, 107, 47));
    _cacheColor("olivedrab", Util::encodeColor(107, 142, 35));
    _cacheColor("lightcyan", Util::encodeColor(224, 255, 255));
    _cacheColor("cyan", Util::encodeColor(0, 255, 255));
    _cacheColor("aqua", Util::encodeColor(0, 255, 255));
    _cacheColor("aquamarine", Util::encodeColor(127, 255, 212));
    _cacheColor("mediumaquamarine", Util::encodeColor(102, 205, 170));
    _cacheColor("paleturquoise", Util::encodeColor(175, 238, 238));
    _cacheColor("turquoise", Util::encodeColor(64, 224, 208));
    _cacheColor("mediumturquoise", Util::encodeColor(72, 209, 204));
    _cacheColor("darkturquoise", Util::encodeColor(0, 206, 209));
    _cacheColor("lightseagreen", Util::encodeColor(32, 178, 170));
    _cacheColor("cadetblue", Util::encodeColor(95, 158, 160));
    _cacheColor("darkcyan", Util::encodeColor(0, 139, 139));
    _cacheColor("teal", Util::encodeColor(0, 128, 128));
    _cacheColor("powderblue", Util::encodeColor(176, 224, 230));
    _cacheColor("lightblue", Util::encodeColor(173, 216, 230));
    _cacheColor("lightskyblue", Util::encodeColor(135, 206, 250));
    _cacheColor("skyblue", Util::encodeColor(135, 206, 235));
    _cacheColor("deepskyblue", Util::encodeColor(0, 191, 255));
    _cacheColor("lightsteelblue", Util::encodeColor(176, 196, 222));
    _cacheColor("dodgerblue", Util::encodeColor(30, 144, 255));
    _cacheColor("cornflowerblue", Util::encodeColor(100, 149, 237));
    _cacheColor("steelblue", Util::encodeColor(70, 130, 180));
    _cacheColor("royalblue", Util::encodeColor(65, 105, 225));
    _cacheColor("blue", Util::encodeColor(0, 0, 255));
    _cacheColor("mediumblue", Util::encodeColor(0, 0, 205));
    _cacheColor("darkblue", Util::encodeColor(0, 0, 139));
    _cacheColor("navy", Util::encodeColor(0, 0, 128));
    _cacheColor("midnightblue", Util::encodeColor(25, 25, 112));
    _cacheColor("mediumslateblue", Util::encodeColor(123, 104, 238));
    _cacheColor("slateblue", Util::encodeColor(106, 90, 205));
    _cacheColor("darkslateblue", Util::encodeColor(72, 61, 139));
    _cacheColor("lavender", Util::encodeColor(230, 230, 250));
    _cacheColor("thistle", Util::encodeColor(216, 191, 216));
    _cacheColor("plum", Util::encodeColor(221, 160, 221));
    _cacheColor("violet", Util::encodeColor(238, 130, 238));
    _cacheColor("orchid", Util::encodeColor(218, 112, 214));
    _cacheColor("fuchsia", Util::encodeColor(255, 0, 255));
    _cacheColor("magenta", Util::encodeColor(255, 0, 255));
    _cacheColor("mediumorchid", Util::encodeColor(186, 85, 211));
    _cacheColor("mediumpurple", Util::encodeColor(147, 112, 219));
    _cacheColor("blueviolet", Util::encodeColor(138, 43, 226));
    _cacheColor("darkviolet", Util::encodeColor(148, 0, 211));
    _cacheColor("darkorchid", Util::encodeColor(153, 50, 204));
    _cacheColor("darkmagenta", Util::encodeColor(139, 0, 139));
    _cacheColor("purple", Util::encodeColor(128, 0, 128));
    _cacheColor("indigo", Util::encodeColor(75, 0, 130));
    _cacheColor("pink", Util::encodeColor(255, 192, 203));
    _cacheColor("lightpink", Util::encodeColor(255, 182, 193));
    _cacheColor("hotpink", Util::encodeColor(255, 105, 180));
    _cacheColor("deeppink", Util::encodeColor(255, 20, 147));
    _cacheColor("palevioletred", Util::encodeColor(219, 112, 147));
    _cacheColor("mediumvioletred", Util::encodeColor(199, 21, 133));
    _cacheColor("white", Util::encodeColor(255, 255, 255));
    _cacheColor("snow", Util::encodeColor(255, 250, 250));
    _cacheColor("honeydew", Util::encodeColor(240, 255, 240));
    _cacheColor("mintcream", Util::encodeColor(245, 255, 250));
    _cacheColor("azure", Util::encodeColor(240, 255, 255));
    _cacheColor("aliceblue", Util::encodeColor(240, 248, 255));
    _cacheColor("ghostwhite", Util::encodeColor(248, 248, 255));
    _cacheColor("whitesmoke", Util::encodeColor(245, 245, 245));
    _cacheColor("seashell", Util::encodeColor(255, 245, 238));
    _cacheColor("beige", Util::encodeColor(245, 245, 220));
    _cacheColor("oldlace", Util::encodeColor(253, 245, 230));
    _cacheColor("floralwhite", Util::encodeColor(255, 250, 240));
    _cacheColor("ivory", Util::encodeColor(255, 255, 240));
    _cacheColor("antiquewhite", Util::encodeColor(250, 235, 215));
    _cacheColor("linen", Util::encodeColor(250, 240, 230));
    _cacheColor("lavenderblush", Util::encodeColor(255, 240, 245));
    _cacheColor("mistyrose", Util::encodeColor(255, 228, 225));
    _cacheColor("gainsboro", Util::encodeColor(220, 220, 220));
    _cacheColor("lightgray", Util::encodeColor(211, 211, 211));
    _cacheColor("silver", Util::encodeColor(192, 192, 192));
    _cacheColor("darkgray", Util::encodeColor(169, 169, 169));
    _cacheColor("gray", Util::encodeColor(128, 128, 128));
    _cacheColor("dimgray", Util::encodeColor(105, 105, 105));
    _cacheColor("lightslategray", Util::encodeColor(119, 136, 153));
    _cacheColor("slategray", Util::encodeColor(112, 128, 144));
    _cacheColor("darkslategray", Util::encodeColor(47, 79, 79));
    _cacheColor("black", Util::encodeColor(0, 0, 0));
    _cacheColor("cornsilk", Util::encodeColor(255, 248, 220));
    _cacheColor("blanchedalmond", Util::encodeColor(255, 235, 205));
    _cacheColor("bisque", Util::encodeColor(255, 228, 196));
    _cacheColor("navajowhite", Util::encodeColor(255, 222, 173));
    _cacheColor("wheat", Util::encodeColor(245, 222, 179));
    _cacheColor("burlywood", Util::encodeColor(222, 184, 135));
    _cacheColor("tan", Util::encodeColor(210, 180, 140));
    _cacheColor("rosybrown", Util::encodeColor(188, 143, 143));
    _cacheColor("sandybrown", Util::encodeColor(244, 164, 96));
    _cacheColor("goldenrod", Util::encodeColor(218, 165, 32));
    _cacheColor("peru", Util::encodeColor(205, 133, 63));
    _cacheColor("chocolate", Util::encodeColor(210, 105, 30));
    _cacheColor("saddlebrown", Util::encodeColor(139, 69, 19));
    _cacheColor("sienna", Util::encodeColor(160, 82, 45));
    _cacheColor("brown", Util::encodeColor(165, 42, 42));
}

sf::Color Context::_parseColor(const char* raw)
{
    auto result = sf::Color::Black;

    char* rawColor = static_cast<char*>(
        calloc(strlen(raw) + 1, sizeof(char))
    );
    
    if (rawColor)
    {
        memcpy(rawColor, raw, strlen(raw) + 1);
    }
    else
    {
        fprintf(stderr, "Failed to allocate memory for color string\n");
        return result;
    }
    
    char* trimmed = Util::trim(rawColor);

    if (trimmed[0] == 0)
    {
        free(rawColor);
        return result;
    }

    if (m_colorCache.find(rawColor) != m_colorCache.end())
    {
        result = Util::extractColor(m_colorCache.at(rawColor));
        free(rawColor);
        return result;
    }

    bool parsed = false;

    size_t trimmedLength = strlen(trimmed);

    if (trimmed[0] == '#')
    {
        if (trimmedLength == 9 || trimmedLength == 7 || trimmedLength == 4)
        {
            trimmed++;
            trimmedLength--;
            char* expandedColor = nullptr;

            if (trimmedLength == 3)
            {
                std::stringstream stream;

                expandedColor = static_cast<char*>(calloc(7, sizeof(char)));

                expandedColor[0] = expandedColor[1] = trimmed[0];
                expandedColor[2] = expandedColor[3] = trimmed[1];
                expandedColor[4] = expandedColor[5] = trimmed[2];
                expandedColor[6] = '\0';

                trimmedLength = 6;
                trimmed = expandedColor;
            }

            uint8_t components[4] = { 0, 0, 0, 255 };

            for (size_t i = 0; i < trimmedLength; i += 2)
            {
                char original = 0;

                if (i < trimmedLength - 2)
                {
                    original = trimmed[2];
                    trimmed[2] = '\0';
                }

                components[i / 2] = static_cast<uint8_t>(
                    std::stoul(trimmed, nullptr, 16)
                );

                if (i < trimmedLength - 2)
                {
                    trimmed[2] = original;
                }

                trimmed += 2;
            }

            if (expandedColor)
            {
                free(expandedColor);
            }

             parsed = true;
             result = sf::Color(
                 components[0], components[1], components[2], components[3]
             );
        }
    }
    // at least 9 chars for rgb(0,0,0) which should be the shortest possible rgb def
    else if (trimmedLength > 9 && trimmed[0] == 'r' && trimmed[1] == 'g' && trimmed[2] == 'b')
    {
        size_t startPosition = trimmed[3] == 'a' ? 4 : 3;

        trimmed += startPosition;
        char* inner = Util::trim(trimmed);
        size_t innerLength = strlen(inner);

        if (inner[0] == '(' && inner[innerLength - 1] == ')')
        {
            //style = style.substr(1, style.size() - 2);

            // Remove the surrounding ()
            inner[innerLength - 1] = '\0';
            inner++;
            innerLength -= 2;

            uint8_t components[] = { 0, 0, 0, 255 };

            char* part;
            char* end;

            part = end = inner;

            size_t componentIndex = 0;
            for (size_t i = 0; i < innerLength; i++)
            {
                // NOTE: This means that the only way for an rgba() color component to get parsed
                //       as a double (i.e. the `a` component), is if that component is at the end
                //       of the string. That should be fine, but I'm not sure if it might cause 
                //       unexpected behavior on malformed rgba strings.
                if (i == innerLength - 1)
                {
                    components[componentIndex] = Util::stringToColorComponent(part, componentIndex == 3);
                    break;
                }

                if (inner[i] == ',')
                {
                    char c = inner[i];
                    end[0] = '\0';
                    
                    components[componentIndex++] = Util::stringToColorComponent(part);

                    part = inner + i + 1;
                    end[0] = c;
                }

                end++;
            }

            inner[innerLength] = ')';
            inner--;

            if (componentIndex > 1)
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
        fprintf(stderr, "Got an invalid color string: %s\n", rawColor);
    }

    printf("Cached color string %s as ", rawColor);
    Util::printColor(result, "\n");

    m_colorCache.insert(
        std::make_pair(rawColor, Util::encodeColor(result))
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
        "Parsed font string: '%s' ->\n{\n  size=%d\n  family=%s\n  bold=%s\n  underlined=%s\n  italic=%s\n}\n",
        fontString.c_str(),
        size,
        family.c_str(),
        bold ? "true" : "false",
        underlined ? "true" : "false",
        italic ? "true" : "false"
    );

    sf::Font* font;
    if ((font = m_canvas->_getFont(family)) != nullptr)
    {
        sf::Text* text = new sf::Text();

        text->setFont(*font);
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
    m_lineJoinString("miter"),
    m_lineJoin(LineJoin::Miter),
    m_lineCapString("butt"),
    m_lineCap(LineCap::Butt),
    m_pathCount(0),
    m_text(nullptr),
    m_fillStyleString(nullptr),
    m_strokeStyle(nullptr)
{
    m_rectangle = new sf::RectangleShape();

    _cacheDefaultColors();

    fillStyle("black");
    strokeStyle("black");
}

Context::~Context()
{
    if (m_rectangle)
        delete m_rectangle;

    if (m_fillStyleString)
        free(m_fillStyleString);

    if (m_strokeStyle)
        free(m_strokeStyle);

    for (auto it = m_texts.begin(); it != m_texts.end(); it++)
        delete it->second;

    for (auto it = m_paths.begin(); it < m_paths.end(); it++)
        delete* it;

    for (auto it = m_colorCache.begin(); it != m_colorCache.end(); it++)    
    { 
        // The pre-cached colors are all alphabetical. Any other colors
        // will be either in the form #BEEFED or rgb()/rgba().
        if (!Util::isAlphabetical(it->first))
        {
            free(it->first);
        }
    }
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

const char* Context::fillStyle() const
{
    return m_fillStyleString;
}

void Context::fillStyle(const char* newStyle)
{
    if (m_fillStyleString)
    {
        free(m_fillStyleString);
    }

    m_fillStyleString = static_cast<char*>(calloc(strlen(newStyle) + 1, sizeof(char)));
    if (m_fillStyleString)
    {
        memcpy(m_fillStyleString, newStyle, strlen(newStyle) + 1);
    }

    m_fillStyle.type = FillStyle::Type::Color;
    m_fillStyle.color = _parseColor(newStyle);
}

void Context::fillStyle(const CanvasGradient& gradient)
{
    m_fillStyle.type = FillStyle::Type::Gradient;
    m_fillStyle.gradient = &gradient;
}

const char* Context::strokeStyle() const
{
    return m_strokeStyle;
}

void Context::strokeStyle(const char* newStyle)
{    
    if (m_strokeStyle)
    {
        free(m_strokeStyle);
    }

    m_strokeStyle = static_cast<char*>(calloc(strlen(newStyle) + 1, sizeof(char)));
    if (m_strokeStyle)
    {
        memcpy(m_strokeStyle, newStyle, strlen(newStyle) + 1);
    }

    m_strokeColor = _parseColor(newStyle);
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
        m_canvas->_sfWindow()->draw(*m_rectangle);
    }
    else
    {
        m_canvas->_sfWindow()->draw(*m_rectangle, CanvasGradient::_getShader(m_fillStyle.gradient));
    }
}

void Context::strokeRect(float x, float y, float width, float height)
{
    m_rectangle->setSize(sf::Vector2f(width - m_lineWidth, height - m_lineWidth));
    m_rectangle->setPosition(sf::Vector2f(x + m_lineWidth / 2, y + m_lineWidth / 2));
    m_rectangle->setFillColor(sf::Color::Transparent);
    m_rectangle->setOutlineColor(m_strokeColor);
    m_rectangle->setOutlineThickness(m_lineWidth);

    m_canvas->_sfWindow()->draw(*m_rectangle);
}

void Context::clearRect()
{
    auto color = _parseColor(m_canvas->backgroundColor().c_str());
    m_canvas->_sfWindow()->clear(color);
}

void Context::clearRect(float x, float y, float width, float height)
{
    auto fs = fillStyle();

    char* backgroundColor = static_cast<char*>(
        calloc(m_canvas->backgroundColor().size() + 1, sizeof(char))
    );

    fillStyle(m_canvas->backgroundColor().c_str());
    fillRect(x, y, width, height);
    fillStyle(fs);
}

void Context::drawImage(const Image& image, float dx, float dy)
{
    sf::Sprite* sprite = image._getSprite();
    sprite->setPosition(sf::Vector2f(dx, dy));
    m_canvas->_sfWindow()->draw(*sprite);
}

void Context::drawImage(const Image& image, float dx, float dy, float dWidth, float dHeight)
{
    sf::Sprite* sprite = image._getSprite();

    sprite->setPosition(sf::Vector2f(dx, dy));

    auto size = sprite->getTexture()->getSize();
    sprite->setScale(sf::Vector2f(dWidth / size.x, dHeight / size.y));

    m_canvas->_sfWindow()->draw(*sprite);
}

void Context::drawImage(const Image& image, float sx, float sy, float sWidth, float sHeight, float dx, float dy, float dWidth, float dHeight)
{
    sf::Sprite* sprite = image._getSprite();

    sf::IntRect rect = sprite->getTextureRect();
    sprite->setTextureRect(sf::IntRect(
        static_cast<int>(sx),
        static_cast<int>(sy),
        static_cast<int>(sWidth),
        static_cast<int>(sHeight)
    ));

    sprite->setPosition(sf::Vector2f(dx, dy));
    sprite->setScale(sf::Vector2f(dWidth / sWidth, dHeight / sHeight));

    m_canvas->_sfWindow()->draw(*sprite);

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
        m_canvas->_sfWindow()->draw(*m_text);
    }
    else
    {
        m_canvas->_sfWindow()->draw(*m_text, CanvasGradient::_getShader(m_fillStyle.gradient));
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

    m_canvas->_sfWindow()->draw(*m_text);
}

TextMetrics Context::measureText(const std::string& string)
{
    if (m_text == nullptr)
    {
        printf("Call to measureText() with no font set.");
        return { 0 };
    }

    m_text->setString(string);
    m_text->setOutlineThickness(0.0f);
    m_text->setFillColor(sf::Color::Transparent);

    m_canvas->_sfWindow()->draw(*m_text);

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
        m_paths.at(i)->stroke(m_lineWidth, m_strokeColor, m_lineJoin, m_lineCap, m_canvas->_sfWindow());
    }
}

void Context::fill()
{
    for (size_t i = 0; i < m_pathCount; i++)
    {
        m_paths.at(i)->fill(m_fillStyle, m_canvas->_sfWindow());
    }
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
