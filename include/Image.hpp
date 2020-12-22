#ifndef _CANVAS_IMAGE_HPP
#define _CANVAS_IMAGE_HPP

#include <SFML/Graphics.hpp>

namespace Canvas
{
class Image
{
public:
    Image();
    Image(const std::string&);
    ~Image();

    void src(const std::string&);
    std::string src() const;

    sf::Sprite* _getSprite() const;

private:
    std::string m_source;

    sf::Sprite* m_sprite;
    sf::Texture* m_texture;
};
}
#endif
