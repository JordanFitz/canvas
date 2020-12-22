#include "Context.hpp"
#include "Image.hpp"

namespace Canvas {
Image::Image()
{
    m_sprite = new sf::Sprite();
    m_texture = new sf::Texture();
}

Image::Image(const std::string& source) : Image()
{
    src(source);
}

Image::~Image()
{
    delete m_sprite;
    delete m_texture;
}

void Image::src(const std::string& source)
{
    m_source = source;
    m_texture = new sf::Texture();
    m_texture->loadFromFile(m_source);
    m_sprite->setTexture(*m_texture);
}

std::string Image::src() const
{
    return m_source;
}

sf::Sprite* Image::_getSprite() const
{
    return m_sprite;
}
}
