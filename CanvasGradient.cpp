#include <string>
#include <SFML\Graphics.hpp>

#include "Context.hpp"
#include "CanvasGradient.hpp"

namespace Canvas {
bool CanvasGradient::_shaderLoaded = false;
sf::Shader CanvasGradient::_shader;

void CanvasGradient::setHeight(const float& height)
{
    _shader.setUniform("windowHeight", height);
}

sf::Shader* CanvasGradient::getShader(const CanvasGradient* gradient)
{
    _shader.setUniform("gradientStartPos", sf::Glsl::Vec2(gradient->m_start));
    _shader.setUniform("gradientEndPos", sf::Glsl::Vec2(gradient->m_end));
    _shader.setUniform("numStops", static_cast<int>(gradient->m_offsets.size()));
    _shader.setUniformArray("colors", &gradient->m_colors[0], gradient->m_colors.size());
    _shader.setUniformArray("stops", &gradient->m_offsets[0], gradient->m_offsets.size());

    return &_shader;
}

CanvasGradient::CanvasGradient():
    m_canvas(nullptr), m_start(0, 0), m_end(0, 0)
{}

CanvasGradient::CanvasGradient(Context* canvas, const float& x1, const float& y1, const float& x2, const float& y2) :
    m_canvas(canvas), m_start(x1, y1), m_end(x2, y2)
{
    if (!_shaderLoaded)
    {
        _shader.loadFromMemory(VERT_SHADER, FRAG_SHADER);
        _shaderLoaded = true;
    }
}

CanvasGradient::~CanvasGradient()
{}

void CanvasGradient::addColorStop(const float& offset, const std::string& color)
{
    m_offsets.push_back(offset);
    m_colors.push_back(m_canvas->parseColor(color));
}
}
