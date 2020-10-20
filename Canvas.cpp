#include "Image.hpp"
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
                style = style + style;
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

Canvas::Canvas() :
    m_width(300),
    m_height(150),
    m_lineWidth(1.0f),
    m_render(nullptr),
    m_update(nullptr)
{
    m_rectangle = new sf::RectangleShape();
    m_window = new sf::RenderWindow(
        sf::VideoMode(m_width, m_height),
        "Canvas", sf::Style::Close
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

}

Canvas::~Canvas()
{
    delete m_window;
    delete m_rectangle;
}

void Canvas::hookUpdate(void (*proc)(Canvas*))
{
    m_update = proc;
}

void Canvas::hookRender(void (*proc)(Canvas*))
{
    m_render = proc;
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
        }

        m_window->clear();

        if(m_update != nullptr) m_update(this);
        if(m_render != nullptr) m_render(this);

        m_window->display();
    }
}

std::string Canvas::fillStyle()
{
    return m_fillStyle;
}

void Canvas::fillStyle(const char* newStyle)
{
    m_fillStyle = std::string(newStyle);
    m_fillColor = _parseColor(m_fillStyle);
}

std::string Canvas::strokeStyle()
{
    return m_strokeStyle;
}

void Canvas::strokeStyle(const char* newStyle)
{
    m_strokeStyle = std::string(newStyle);
}

void Canvas::lineWidth(float newWidth)
{
    m_lineWidth = newWidth;
}

float Canvas::lineWidth()
{
    return m_lineWidth;
}

void Canvas::width(unsigned int newWidth)
{
    m_width = newWidth;
    sf::Vector2u size = m_window->getSize();
    m_window->setSize(sf::Vector2u(m_width, size.y));
}

unsigned int Canvas::width()
{
    return m_width;
}

void Canvas::height(unsigned int newHeight)
{
    m_height = newHeight;
    sf::Vector2u size = m_window->getSize();
    m_window->setSize(sf::Vector2u(size.x, m_height));
}

unsigned int Canvas::height()
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
