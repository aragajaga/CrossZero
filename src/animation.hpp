#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <SFML/System.hpp>

extern sf::Clock animationClock;

class Animation {
public:
    void play()
    {
        if (m_playing && !m_doInterrupt)
            return;
        
        m_playing = true;
        m_startTime = animationClock.getElapsedTime();
    }
    
    bool isPlaying() const {
        return m_playing;
    }
    
    sf::Time getElapsed() const
    {
        return animationClock.getElapsedTime() - m_startTime;
    }
    
    void stop()
    {
        m_startTime = sf::Time::Zero;
        m_playing = false;
    }
private:
    bool m_doInterrupt;
    bool m_playing;
    
    sf::Time m_startTime;
};

#endif // ANIMATION_HPP
