#include "Canvas.hpp"
#include "Image.hpp"

namespace Canvas {
Image::Image()
{
    m_sprite = new sf::Sprite();
    m_texture = new sf::Texture();
}

Image::Image(const char* source) : Image()
{
    src(source);
}

Image::~Image()
{
    delete m_sprite;
    delete m_texture;
}

void Image::src(const char* source)
{
    m_texture = new sf::Texture();
    m_texture->loadFromFile(source);
    m_sprite->setTexture(*m_texture);
}

sf::Sprite* Image::getSprite() const
{
    return m_sprite;
}
}
