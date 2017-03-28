/////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARTICLE_HPP
#define PARTICLE_HPP
/////////////////////////////////////////////////////////////////////////////////////////
#include "particle_traits.hpp"
#include "particle_container.hpp"
/////////////////////////////////////////////////////////////////////////////////////////
template<typename PartTraits>
class Particle
{
public:
    typedef containerType::traits traits;
    
    typedef typename std::conditional<
                    std::is_base_of<DefaultParticleTraits, PartTraits>::value, 
                        ParticleContainer<PartTraits>,
                        PartTraits
            >::type 
        containerType;

    Particle(const ParticleContainer& container);
    
    const traits::timerType& getTimer() const;
    
    traits::timerType& getTimer();
    
    const traits::speedType& getSpeed() const;
    
    void setSpeed(const traits::speedType& speed);
    
    const traits::windowSizeType& getWindowSize() const;
    
    const traits::spritesType& getSprites() const;

    traits::spritesType& getSprites();
    
    const traits::anglesType& getAngles() const;
    
    traits::anglesType& getAngles();
    
    const traits::texturesType& getTextures() const;
    
    traits::texturesType& getTextures();
    
    void add(const traits::elemDataType& elem);
    
    template<typename PreStartFunction, typename... AdditionalParams>
    void preStartConfigure(PreStartFunction* function, AdditionalParams&&... params);
    
    template<typename FunctionType, typename... AdditionalParams>
    void update(FunctionType* updateFunc, AdditionalParams&&... params);
    
private:
    containerType container;
};
/////////////////////////////////////////////////////////////////////////////////////////
#endif //PARTICLE_HPP
/////////////////////////////////////////////////////////////////////////////////////////