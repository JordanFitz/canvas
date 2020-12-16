#ifndef _CANVAS_IMAGE_HPP
#define _CANVAS_IMAGE_HPP

#include <SFML/Graphics.hpp>

namespace Canvas
{
class Image
{
public:
    Image();
    Image(const char*);
    ~Image();

    void src(const char*);

    sf::Sprite* getSprite() const;

private:
    sf::Sprite* m_sprite;
    sf::Texture* m_texture;
};
}
#endif
