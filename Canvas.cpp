#include "Image.hpp"
#include "Path.hpp"
#include "TextMetrics.hpp"
#include "Canvas.hpp"
#include "util.hpp"

sf::Color Canvas::_parseColor(std::string& style)
{
    auto result = sf::Color::Black;

    trim(style);

    if (style.length() == 0)
    {
        return result;
    }

    std::transform(style.begin(), style.end(), style.begin(), [](unsigned char c) {
        return std::tolower(c);
    });

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
        trim(style);

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
                    trim(part);

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
                trim(part);
                
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
    if(!parsed)
    {
        fprintf(stderr, "Got an invalid color string: %s\n", originalStyle.c_str());
    }

    printf("Cached color string %s as ", originalStyle.c_str());
    printColor(result, "\n");

    m_colorCache.insert(
        std::pair<std::string, sf::Color>(originalStyle, result)
    );

    return result;
}

void Canvas::_registerColor(const char* name, const sf::Color& color)
{
    m_colorCache.insert(std::pair<std::string, sf::Color>(name, color));
}

sf::Text* Canvas::_parseFontString(std::string& fontString)
{
    trim(fontString);

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
            trim(part);
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
        trim(part);
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

Canvas::Canvas() :
    m_width(300),
    m_height(150),
    m_lineWidth(1.0f),
    m_render(nullptr),
    m_update(nullptr),
    m_backgroundColor("white"),
    m_lineJoinString("miter"),
    m_lineJoin(LineJoin::Miter)
{
    m_rectangle = new sf::RectangleShape();

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    m_window = new sf::RenderWindow(
        sf::VideoMode(m_width, m_height),
        "Canvas", sf::Style::Close, settings
    );

    _registerColor("lightsalmon", sf::Color(255, 160, 122));
    _registerColor("salmon", sf::Color(250, 128, 114));
    _registerColor("darksalmon", sf::Color(233, 150, 122));
    _registerColor("lightcoral", sf::Color(240, 128, 128));
    _registerColor("indianred", sf::Color(205, 92, 92));
    _registerColor("crimson", sf::Color(220, 20, 60));
    _registerColor("firebrick", sf::Color(178, 34, 34));
    _registerColor("red", sf::Color(255, 0, 0));
    _registerColor("darkred", sf::Color(139, 0, 0));
    _registerColor("coral", sf::Color(255, 127, 80));
    _registerColor("tomato", sf::Color(255, 99, 71));
    _registerColor("orangered", sf::Color(255, 69, 0));
    _registerColor("gold", sf::Color(255, 215, 0));
    _registerColor("orange", sf::Color(255, 165, 0));
    _registerColor("darkorange", sf::Color(255, 140, 0));
    _registerColor("lightyellow", sf::Color(255, 255, 224));
    _registerColor("lemonchiffon", sf::Color(255, 250, 205));
    _registerColor("lightgoldenrodyellow", sf::Color(250, 250, 210));
    _registerColor("papayawhip", sf::Color(255, 239, 213));
    _registerColor("moccasin", sf::Color(255, 228, 181));
    _registerColor("peachpuff", sf::Color(255, 218, 185));
    _registerColor("palegoldenrod", sf::Color(238, 232, 170));
    _registerColor("khaki", sf::Color(240, 230, 140));
    _registerColor("darkkhaki", sf::Color(189, 183, 107));
    _registerColor("yellow", sf::Color(255, 255, 0));
    _registerColor("lawngreen", sf::Color(124, 252, 0));
    _registerColor("chartreuse", sf::Color(127, 255, 0));
    _registerColor("limegreen", sf::Color(50, 205, 50));
    _registerColor("lime", sf::Color(0, 255, 0));
    _registerColor("forestgreen", sf::Color(34, 139, 34));
    _registerColor("green", sf::Color(0, 128, 0));
    _registerColor("darkgreen", sf::Color(0, 100, 0));
    _registerColor("greenyellow", sf::Color(173, 255, 47));
    _registerColor("yellowgreen", sf::Color(154, 205, 50));
    _registerColor("springgreen", sf::Color(0, 255, 127));
    _registerColor("mediumspringgreen", sf::Color(0, 250, 154));
    _registerColor("lightgreen", sf::Color(144, 238, 144));
    _registerColor("palegreen", sf::Color(152, 251, 152));
    _registerColor("darkseagreen", sf::Color(143, 188, 143));
    _registerColor("mediumseagreen", sf::Color(60, 179, 113));
    _registerColor("seagreen", sf::Color(46, 139, 87));
    _registerColor("olive", sf::Color(128, 128, 0));
    _registerColor("darkolivegreen", sf::Color(85, 107, 47));
    _registerColor("olivedrab", sf::Color(107, 142, 35));
    _registerColor("lightcyan", sf::Color(224, 255, 255));
    _registerColor("cyan", sf::Color(0, 255, 255));
    _registerColor("aqua", sf::Color(0, 255, 255));
    _registerColor("aquamarine", sf::Color(127, 255, 212));
    _registerColor("mediumaquamarine", sf::Color(102, 205, 170));
    _registerColor("paleturquoise", sf::Color(175, 238, 238));
    _registerColor("turquoise", sf::Color(64, 224, 208));
    _registerColor("mediumturquoise", sf::Color(72, 209, 204));
    _registerColor("darkturquoise", sf::Color(0, 206, 209));
    _registerColor("lightseagreen", sf::Color(32, 178, 170));
    _registerColor("cadetblue", sf::Color(95, 158, 160));
    _registerColor("darkcyan", sf::Color(0, 139, 139));
    _registerColor("teal", sf::Color(0, 128, 128));
    _registerColor("powderblue", sf::Color(176, 224, 230));
    _registerColor("lightblue", sf::Color(173, 216, 230));
    _registerColor("lightskyblue", sf::Color(135, 206, 250));
    _registerColor("skyblue", sf::Color(135, 206, 235));
    _registerColor("deepskyblue", sf::Color(0, 191, 255));
    _registerColor("lightsteelblue", sf::Color(176, 196, 222));
    _registerColor("dodgerblue", sf::Color(30, 144, 255));
    _registerColor("cornflowerblue", sf::Color(100, 149, 237));
    _registerColor("steelblue", sf::Color(70, 130, 180));
    _registerColor("royalblue", sf::Color(65, 105, 225));
    _registerColor("blue", sf::Color(0, 0, 255));
    _registerColor("mediumblue", sf::Color(0, 0, 205));
    _registerColor("darkblue", sf::Color(0, 0, 139));
    _registerColor("navy", sf::Color(0, 0, 128));
    _registerColor("midnightblue", sf::Color(25, 25, 112));
    _registerColor("mediumslateblue", sf::Color(123, 104, 238));
    _registerColor("slateblue", sf::Color(106, 90, 205));
    _registerColor("darkslateblue", sf::Color(72, 61, 139));
    _registerColor("lavender", sf::Color(230, 230, 250));
    _registerColor("thistle", sf::Color(216, 191, 216));
    _registerColor("plum", sf::Color(221, 160, 221));
    _registerColor("violet", sf::Color(238, 130, 238));
    _registerColor("orchid", sf::Color(218, 112, 214));
    _registerColor("fuchsia", sf::Color(255, 0, 255));
    _registerColor("magenta", sf::Color(255, 0, 255));
    _registerColor("mediumorchid", sf::Color(186, 85, 211));
    _registerColor("mediumpurple", sf::Color(147, 112, 219));
    _registerColor("blueviolet", sf::Color(138, 43, 226));
    _registerColor("darkviolet", sf::Color(148, 0, 211));
    _registerColor("darkorchid", sf::Color(153, 50, 204));
    _registerColor("darkmagenta", sf::Color(139, 0, 139));
    _registerColor("purple", sf::Color(128, 0, 128));
    _registerColor("indigo", sf::Color(75, 0, 130));
    _registerColor("pink", sf::Color(255, 192, 203));
    _registerColor("lightpink", sf::Color(255, 182, 193));
    _registerColor("hotpink", sf::Color(255, 105, 180));
    _registerColor("deeppink", sf::Color(255, 20, 147));
    _registerColor("palevioletred", sf::Color(219, 112, 147));
    _registerColor("mediumvioletred", sf::Color(199, 21, 133));
    _registerColor("white", sf::Color(255, 255, 255));
    _registerColor("snow", sf::Color(255, 250, 250));
    _registerColor("honeydew", sf::Color(240, 255, 240));
    _registerColor("mintcream", sf::Color(245, 255, 250));
    _registerColor("azure", sf::Color(240, 255, 255));
    _registerColor("aliceblue", sf::Color(240, 248, 255));
    _registerColor("ghostwhite", sf::Color(248, 248, 255));
    _registerColor("whitesmoke", sf::Color(245, 245, 245));
    _registerColor("seashell", sf::Color(255, 245, 238));
    _registerColor("beige", sf::Color(245, 245, 220));
    _registerColor("oldlace", sf::Color(253, 245, 230));
    _registerColor("floralwhite", sf::Color(255, 250, 240));
    _registerColor("ivory", sf::Color(255, 255, 240));
    _registerColor("antiquewhite", sf::Color(250, 235, 215));
    _registerColor("linen", sf::Color(250, 240, 230));
    _registerColor("lavenderblush", sf::Color(255, 240, 245));
    _registerColor("mistyrose", sf::Color(255, 228, 225));
    _registerColor("gainsboro", sf::Color(220, 220, 220));
    _registerColor("lightgray", sf::Color(211, 211, 211));
    _registerColor("silver", sf::Color(192, 192, 192));
    _registerColor("darkgray", sf::Color(169, 169, 169));
    _registerColor("gray", sf::Color(128, 128, 128));
    _registerColor("dimgray", sf::Color(105, 105, 105));
    _registerColor("lightslategray", sf::Color(119, 136, 153));
    _registerColor("slategray", sf::Color(112, 128, 144));
    _registerColor("darkslategray", sf::Color(47, 79, 79));
    _registerColor("black", sf::Color(0, 0, 0));
    _registerColor("cornsilk", sf::Color(255, 248, 220));
    _registerColor("blanchedalmond", sf::Color(255, 235, 205));
    _registerColor("bisque", sf::Color(255, 228, 196));
    _registerColor("navajowhite", sf::Color(255, 222, 173));
    _registerColor("wheat", sf::Color(245, 222, 179));
    _registerColor("burlywood", sf::Color(222, 184, 135));
    _registerColor("tan", sf::Color(210, 180, 140));
    _registerColor("rosybrown", sf::Color(188, 143, 143));
    _registerColor("sandybrown", sf::Color(244, 164, 96));
    _registerColor("goldenrod", sf::Color(218, 165, 32));
    _registerColor("peru", sf::Color(205, 133, 63));
    _registerColor("chocolate", sf::Color(210, 105, 30));
    _registerColor("saddlebrown", sf::Color(139, 69, 19));
    _registerColor("sienna", sf::Color(160, 82, 45));
    _registerColor("brown", sf::Color(165, 42, 42));

    fillStyle("black");
    strokeStyle("black");
}

Canvas::~Canvas()
{
    delete m_window;
    delete m_rectangle;
    delete m_currentPath;

    for (auto it = m_fonts.begin(); it != m_fonts.end(); it++)
    {
        delete it->second;
    }

    for (auto it = m_texts.begin(); it != m_texts.end(); it++)
    {
        delete it->second;
    }
}

void Canvas::hookUpdate(void (*proc)(Canvas&))
{
    m_update = proc;
}

void Canvas::hookRender(void (*proc)(Canvas&))
{
    m_render = proc;
}

void Canvas::loadFont(const char* _name, const char* path)
{
    auto name = std::string(_name);

    if (m_fonts.find(name) != m_fonts.end())
    {
        printf("Replacing font '%s'\n", _name);
    }

    sf::Font* font = new sf::Font();
    font->loadFromFile(path);
    m_fonts.insert(std::pair<std::string, sf::Font*>(name, font));
}

void Canvas::initialize()
{
    while (m_window->isOpen())
    {
        sf::Event event;
        while (m_window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                m_window->close();
            }
            if (event.type == sf::Event::Resized)
            {
                sf::FloatRect visibleArea(
                    0, 0,
                    static_cast<float>(event.size.width),
                    static_cast<float>(event.size.height)
                );
                m_window->setView(sf::View(visibleArea));
            }

            switch (event.type)
            {
            case sf::Event::Closed:
                dispatchEvent("unload", event);
                break;
            case sf::Event::Resized:
                dispatchEvent("resize", event);
                break;
            case sf::Event::KeyPressed:
                dispatchEvent("keypress", event);
                break;
            case sf::Event::KeyReleased:
                dispatchEvent("keyup", event);
                break;
            case sf::Event::MouseButtonPressed:
                dispatchEvent("mousedown", event);
                break;
            case sf::Event::MouseButtonReleased:
                dispatchEvent("mouseup", event);
                break;
            case sf::Event::MouseMoved:
                dispatchEvent("mousemove", event);
                break;
            case sf::Event::MouseWheelScrolled:
                dispatchEvent("wheel", event);
                break;
            case sf::Event::GainedFocus:
                dispatchEvent("focus", event);
                break;
            case sf::Event::LostFocus:
                dispatchEvent("blur", event);
                break;
            }
        }

        if(m_update != nullptr) m_update(*this);
        if(m_render != nullptr) m_render(*this);

        m_window->display();
    }
}

void Canvas::font(const char* fontString)
{
    m_fontString = std::string(fontString);
    m_text = _parseFontString(m_fontString);
}

const char* Canvas::font() const
{
    return m_fontString.c_str();
}

const char* Canvas::fillStyle() const
{
    return m_fillStyle.c_str();
}

void Canvas::fillStyle(const char* newStyle)
{
    m_fillStyle = std::string(newStyle);
    m_fillColor = _parseColor(m_fillStyle);
}

const char* Canvas::strokeStyle() const
{
    return m_strokeStyle.c_str();
}

void Canvas::strokeStyle(const char* newStyle)
{
    m_strokeStyle = std::string(newStyle);
    m_strokeColor = _parseColor(m_strokeStyle);
}

void Canvas::lineWidth(float newWidth)
{
    m_lineWidth = newWidth;
}

float Canvas::lineWidth() const
{
    return m_lineWidth;
}

void Canvas::width(unsigned int newWidth)
{
    m_width = newWidth;
    sf::Vector2u size = m_window->getSize();
    m_window->setSize(sf::Vector2u(m_width, size.y));
}

unsigned int Canvas::width() const
{
    return m_width;
}

void Canvas::height(unsigned int newHeight)
{
    m_height = newHeight;
    sf::Vector2u size = m_window->getSize();
    m_window->setSize(sf::Vector2u(size.x, m_height));
}

unsigned int Canvas::height() const
{
    return m_height;
}

void Canvas::fillRect(float x, float y, float width, float height)
{
    m_rectangle->setSize(sf::Vector2f(width, height));
    m_rectangle->setPosition(sf::Vector2f(x, y));
    m_rectangle->setFillColor(m_fillColor);
    m_rectangle->setOutlineThickness(0.0f);
    m_window->draw(*m_rectangle);
}

void Canvas::strokeRect(float x, float y, float width, float height)
{
    m_rectangle->setSize(sf::Vector2f(width - m_lineWidth, height - m_lineWidth));
    m_rectangle->setPosition(sf::Vector2f(x + m_lineWidth / 2, y + m_lineWidth / 2));
    m_rectangle->setFillColor(sf::Color::Transparent);
    m_rectangle->setOutlineColor(m_strokeColor);
    m_rectangle->setOutlineThickness(m_lineWidth);

    m_window->draw(*m_rectangle);
}

void Canvas::clearRect()
{
    auto color = _parseColor(m_backgroundColor);
    m_window->clear(color);
}

void Canvas::clearRect(float x, float y, float width, float height)
{
    auto fs = fillStyle();

    fillStyle(m_backgroundColor.c_str());
    fillRect(x, y, width, height);
    fillStyle(fs);
}

void Canvas::drawImage(const Image& image, float dx, float dy)
{
    sf::Sprite* sprite = image.getSprite();
    sprite->setPosition(sf::Vector2f(dx, dy));
    m_window->draw(*sprite);
}

void Canvas::drawImage(const Image& image, float dx, float dy, float dWidth, float dHeight)
{
    sf::Sprite* sprite = image.getSprite();

    sprite->setPosition(sf::Vector2f(dx, dy));

    auto size = sprite->getTexture()->getSize();
    sprite->setScale(sf::Vector2f(dWidth / size.x, dHeight / size.y));

    m_window->draw(*sprite);
}

void Canvas::drawImage(const Image& image, float sx, float sy, float sWidth, float sHeight, float dx, float dy, float dWidth, float dHeight)
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

    m_window->draw(*sprite);

    sprite->setTextureRect(rect);
}

void Canvas::fillText(const char* string, float x, float y)
{
    if (m_text == nullptr)
    {
        printf("Call to fillText() with no font set.");
        return;
    }

    m_text->setFillColor(m_fillColor);
    m_text->setOutlineThickness(0.0f);

    m_text->setPosition(sf::Vector2f(x, y));
    m_text->setString(string);

    m_window->draw(*m_text);
}

void Canvas::strokeText(const char* string, float x, float y)
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

    m_window->draw(*m_text);
}

TextMetrics Canvas::measureText(const char* string)
{
    m_text->setString(string);
    m_text->setOutlineThickness(0.0f);
    m_text->setFillColor(sf::Color::Transparent);

    m_window->draw(*m_text);

    return { m_text->getLocalBounds().width };
}

void Canvas::addEventListener(const char* _type, void (*handler)(const sf::Event&))
{
    std::string type(_type);
    if (m_handlers.find(type) == m_handlers.end())
    {
        m_handlers.insert(
            std::pair<std::string, std::vector<void (*)(const sf::Event&)>>
            (type, std::vector<void (*)(const sf::Event&)>())
        );
    }

    m_handlers.at(type).push_back(handler);
}

void Canvas::dispatchEvent(const char* _type, const sf::Event& event)
{
    std::string type(_type);

    if (m_handlers.find(type) == m_handlers.end())
    {
        return;
    }

    auto handlers = m_handlers.at(type);
    for (auto it = handlers.begin(); it < handlers.end(); it++)
    {
        auto handler = *it;
        handler(event);
    }
}

void Canvas::beginPath()
{
    if (m_currentPath == nullptr)
    {
        m_currentPath = new Path();
    }

    m_currentPath->reset();
}

void Canvas::moveTo(float x, float y)
{
    if (m_currentPath == nullptr || !m_currentPath->empty())
    {
        return;
    }

    m_currentPath->addVertex(x, y);
}

void Canvas::lineTo(float x, float y)
{
    if (m_currentPath == nullptr || m_currentPath->empty())
    {
        return;
    }

    m_currentPath->addVertex(x, y);
}

void Canvas::closePath()
{
    m_currentPath->close();
}

void Canvas::stroke()
{
    m_currentPath->lineJoin(m_lineJoin);
    m_currentPath->draw(m_lineWidth, m_strokeColor, m_window);
}

void Canvas::backgroundColor(const char* style)
{
    m_backgroundColor = std::string(style);
}

const char* Canvas::backgroundColor() const
{
    return m_backgroundColor.c_str();
}

void Canvas::lineJoin(const char* join)
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

const char* Canvas::lineJoin() const
{
    return m_lineJoinString.c_str();
}
