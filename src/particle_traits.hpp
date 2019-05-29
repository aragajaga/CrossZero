//---------------------------------------------------------------------------------------
#ifndef PARTICLE_TRAITS_HPP
#define PARTICLE_TRAITS_HPP
//---------------------------------------------------------------------------------------
#include "tools/timer.hpp"

#include <vector>
#include <utility>
#include <memory>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
//---------------------------------------------------------------------------------------
namespace parts
{
//---------------------------------------------------------------------------------------
struct DefaultParticleTraits
{
    typedef tools::Timer timerType;
    typedef float speedType;
    typedef std::pair<int, int> windowSizeType;
    typedef std::vector<sf::Sprite> spritesType;
    typedef std::vector<float> anglesType;
    typedef std::vector<sf::Texture> texturesType;
    typedef std::tuple<std::string, sf::IntRect, unsigned> elemDataType;
    typedef std::vector<std::tuple<std::string, sf::IntRect, unsigned>> dataType;
};
//---------------------------------------------------------------------------------------
} //parts
//---------------------------------------------------------------------------------------
#endif //PARTICLE_TRAITS_HPP
