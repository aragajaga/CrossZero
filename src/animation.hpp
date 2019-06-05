#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

sf::Color mix(sf::Color a, sf::Color b, float alpha);

extern sf::Clock animationClock;

class Animation; // Forward decl for vector bellow
extern std::vector<Animation *> animations;

class Animation {
public:
    Animation()
    : m_playing(false),
      m_doInterrupt(false),
      m_startTime(sf::Time::Zero)
    {
        animations.push_back(this);
    }

    virtual void onTick() = 0;

    void play()
    {
        #ifdef DEBUG
        std::cout << "[FadeAnimation] Start playing" << std::endl;
        #endif
        
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

class FadeAnimation : public Animation {
public:
    FadeAnimation(sf::Shape *target, sf::Time duration)
    : m_target(target),
      m_duration(duration)
    {}
    
    void play(const sf::Color& destColor)
    {
        Animation::play();
        
        m_startColor = m_target->getFillColor();
        m_destColor = destColor;
    }
    
    void onTick()
    {
        if (isPlaying())
        {
            #ifdef DEBUG
            std::cout << "[FadeAnimation] Tick" << std::endl;
            #endif
            
            float delta = getElapsed() / m_duration;
            
            if (delta > 1.f)
                stop();
            // BUG: Rough destination number
            // TODO: force d=1.f at last tick
            else
                m_target->setFillColor(
                        mix(m_startColor, m_destColor, 1.f - delta));
        }
    }

private:
    sf::Shape *m_target;
    sf::Color m_startColor;
    sf::Color m_destColor;
    sf::Time m_duration;
};

#endif // ANIMATION_HPP
