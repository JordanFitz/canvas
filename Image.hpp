#pragma once

#include <SFML/Graphics.hpp>

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
