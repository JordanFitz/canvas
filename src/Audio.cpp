#include "Audio.hpp"

namespace Canvas
{
Audio::Audio(const std::string& source, bool useStream) :
    m_source(source),
    m_stream(useStream)
{
    src(source);
}

Audio::~Audio()
{}

void Audio::src(const std::string& source)
{
    if (m_stream)
    {
        m_opened = m_music.openFromFile(source);
    }
    else
    {
        m_opened = m_buffer.loadFromFile(source);
        m_sound.setBuffer(m_buffer);
    }
}

const std::string& Audio::src() const
{
    return m_source;
}

void Audio::stream(bool useStream)
{
    m_stream = useStream;
}

bool Audio::stream() const
{
    return m_stream;
}

void Audio::play()
{
    if (!m_opened)
    {
        //TODO: Maybe have an error message/warning here?
        return;
    }

    if (m_stream)
    {
        m_music.play();
    }
    else
    {
        m_sound.play();
    }
}

void Audio::pause()
{
    if (!m_opened)
    {
        //TODO: Maybe have an error message/warning here?
        return;
    }

    if (m_stream)
    {
        m_music.pause();
    }
    else
    {
        m_sound.pause();
    }
}


void Audio::stop()
{
    if (!m_opened)
    {
        //TODO: Maybe have an error message/warning here?
        return;
    }

    if (m_stream)
    {
        m_music.stop();
    }
    else
    {
        m_sound.stop();
    }
}

}
