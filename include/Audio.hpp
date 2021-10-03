#ifndef _CANVAS_AUDIO_HPP
#define _CANVAS_AUDIO_HPP

#include <SFML/Audio.hpp>

namespace Canvas
{
class Audio
{
public:
    Audio(bool useStream = false);
    Audio(const std::string&, bool useStream = false);
    ~Audio();

    void src(const std::string&);
    const std::string& src() const;

    void volume(float);
    float volume() const;

    void stream(bool);
    bool stream() const;

    void play();
    void pause();
    void stop();

    bool playing() const;

private:
    sf::SoundBuffer m_buffer;
    sf::Sound m_sound;
    sf::Music m_music;

    bool m_stream, m_opened;

    std::string m_source;

};
}

#endif
