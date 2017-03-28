/////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARTICLE_CONTAINER_HPP
#define PARTICLE_CONTAINER_HPP
/////////////////////////////////////////////////////////////////////////////////////////
#include "particle_traits.hpp"

template<typename ParticleTraits = DefaultParticleTraits>
struct ParticleContainer
{
    ParticleContainer() = default;
    
    ~ParticleContainer()
    {
        sprites.clear();
        angles.clear();
        textures.clear();
    }
    
    ParticleContainer(const ParticleContainer& parts)
    {
        timer.restart();
        
        speed = parts.speed;
        windowSize = parts.windowSize;
        sprites = parts.sprites;
        angles = parts.angles;
        textures = parts.textures;
        data = parts.data;
    }
    
    ParticleContainer(ParticleContainer&& parts)
    {
        timer.restart;
        
        speed = parts.speed;
        windowSize = parts.windowSize;
        sprites = std::move(parts.sprites);
        angles = std::move(parts.angles);
        textures = std::move(parts.textures);
        data = std::move(parts.data);
    }
    
    ParticleContainer& operator=(const ParticleContainer& parts)
    {
        timer.restart();
        
        speed = parts.speed;
        windowSize = parts.windowSize;
        sprites = parts.sprites;
        angles = parts.angles;
        textures = parts.textures;
        data = parts.data;
        
        return *this;
    }
    
    typedef ParticleTraits traits;
    
    traits::timerType Timer;
    traits::speedType speed;
    traits::windowSizeType windowSize;
    
    traits::spritesType sprites;
    traits::angleType angles;
    traits::textureType textures;
    traits::dataType data;
};
/////////////////////////////////////////////////////////////////////////////////////////
#endif //PARTICLE_CONTAINER_HPP
/////////////////////////////////////////////////////////////////////////////////////////