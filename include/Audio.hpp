#ifndef _CANVAS_AUDIO_HPP
#define _CANVAS_AUDIO_HPP

#include <SFML/Audio.hpp>

namespace Canvas
{
class Audio
{
public:
    Audio(const std::string&, bool useStream = false);
    ~Audio();

    void src(const std::string&);
    const std::string& src() const;

    void stream(bool);
    bool stream() const;

    void play();
    void pause();
    void stop();

private:
    sf::SoundBuffer m_buffer;
    sf::Sound m_sound;
    sf::Music m_music;

    bool m_stream, m_opened;

    std::string m_source;

};
}

#endif
