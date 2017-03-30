//---------------------------------------------------------------------------------------
// Created by GbaLog
// Link on github.com: https://github.com/GbaLog/
//---------------------------------------------------------------------------------------
#include <vector>
#include <SFML/Graphics.hpp>

#include "tools/timer.hpp"
#include "tools/random.hpp"
#include "tools/math.hpp"

#include "simple_particles.hpp"

using tools::random;
//---------------------------------------------------------------------------------------
void box(SimpleParticles& parts)
{
    const int& windowWidth = parts.getWindowSize().first;
    const int& windowHeight = parts.getWindowSize().second;
    auto& sprites = parts.getSprites();
    auto& angles = parts.getAngles();
    for( size_t it{}; it < sprites.size(); ++it )
    {
        sprites[it].move(
            std::cos(angles[it]) * parts.getFactor(), 
            std::sin(angles[it]) * parts.getFactor()
        );

        //check collision with walls
        if (sprites[it].getPosition().x - sprites[it].getOrigin().x < 0)
        {
            angles[it] = PI - angles[it];
            sprites[it].setPosition(
                sprites[it].getOrigin().x + 1,
                sprites[it].getPosition().y
            );
        }
        if (sprites[it].getPosition().x + sprites[it].getOrigin().x > windowWidth + 1)
        {
            angles[it] = PI - angles[it];
            sprites[it].setPosition(
                windowWidth - sprites[it].getOrigin().x + 1,
                sprites[it].getPosition().y
            );
        }
        if (sprites[it].getPosition().y - sprites[it].getOrigin().y < 0)
        {
            angles[it] = -angles[it];
            sprites[it].setPosition(
                sprites[it].getPosition().x,
                sprites[it].getOrigin().y + 1
            );
        }
        if (sprites[it].getPosition().y + sprites[it].getOrigin().y > windowHeight + 1)
        {
            angles[it] = -angles[it];
            sprites[it].setPosition(
                sprites[it].getPosition().x,
                windowHeight - sprites[it].getOrigin().y + 1
            );
        }
        sprites[it].rotate(1);
    }
    parts.getTimer().restart();
}
//---------------------------------------------------------------------------------------
void blizzard(SimpleParticles& parts, float direction)
{
    const int& windowWidth = parts.getWindowSize().first;
    const int& windowHeight = parts.getWindowSize().second;
    auto& sprites = parts.getSprites();
    auto& angles = parts.getAngles();
    for(auto beg = angles.begin(), end = angles.end(); beg != end; ++beg)
    {
        if(*beg != direction)
            *beg = direction;
    }
    
    auto eraseAndAddNew =
        [&] (decltype(sprites.begin()) beg)
        {
            angles.erase(angles.begin() + (beg - sprites.begin()));
            auto cpy = *beg;
            beg = sprites.erase(beg);
            sprites.push_back(std::move(cpy));
            sprites.back().setPosition(random(0, windowWidth), random(0, windowHeight));
            angles.emplace_back(direction);
        };

    for( auto beg = sprites.begin(), end = sprites.end(); beg != end; ++beg )
    {
        beg->move(
            std::cos(angles[beg - sprites.begin()]) * parts.getFactor(),
            std::sin(angles[beg - sprites.begin()]) * parts.getFactor()
        );

        if(beg->getPosition().y - beg->getOrigin().y > windowHeight + 1)
        {
            eraseAndAddNew(beg);
            continue;
        }
        if(beg->getPosition().x - beg->getOrigin().x > windowWidth + 1)
        {
            eraseAndAddNew(beg);
            continue;
        }
        if(beg->getPosition().y + beg->getOrigin().y < 0.f)
        {
            eraseAndAddNew(beg);
            continue;
        }
        if(beg->getPosition().x + beg->getOrigin().x < 0.f)
        {
            eraseAndAddNew(beg);
            continue;
        }
        beg->rotate(1);
    }
    parts.getTimer().restart();
}
