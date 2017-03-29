/////////////////////////////////////////////////////////////////////////////////////////
// Created by GbaLog
// Link on github.com: https://github.com/GbaLog/
/////////////////////////////////////////////////////////////////////////////////////////
#ifndef SIMPLE_PARTICLES
#define SIMPLE_PARTICLES
/////////////////////////////////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <cmath>
#include <ctime>
#include <random>
#include <string>
#include <stdexcept>
#include <vector>
#include <tuple>

#include "tools/timer.hpp"
#include "tools/random.hpp"
#include "tools/math.hpp"

using tools::random;
/////////////////////////////////////////////////////////////////////////////////////////
class SimpleParticles
{

public:

    SimpleParticles(
        std::vector<std::tuple<std::string, sf::IntRect, unsigned>>&& data,
        int windowWidth,
        int windowHeight,
        float speed
    )
        :
        speed{speed},
        windowSize{std::make_pair(windowWidth, windowHeight)},
        windowWidth{windowSize.first},
        windowHeight{windowSize.second}
    {
        for( const auto& it : data )
            add(std::get<0>(it), std::get<1>(it), std::get<2>(it));
    }
    
    tools::Timer& getTimer()
    {
        return timer;
    }
    
    const tools::Timer& getTimer() const
    {
        return timer;
    }

    void setSpeed( const float speed )
    {
        this->speed = speed;
    }
    
    const float getSpeed() const
    {
        return speed;
    }
    
    const float getFactor() const
    {
        return factor;
    }

    void setWindowParams( const int windowWidth, const int windowHeight )
    {
        this->windowWidth = windowWidth;
        this->windowHeight = windowHeight;
    }
    
    const std::pair<int, int>& getWindowSize() const
    {
        return windowSize;
    }
    
    std::vector<sf::Sprite>& getSprites() 
    {
        return sprites;
    }

    const std::vector<sf::Sprite>& getSprites() const
    {
        return sprites;
    }
    
    std::vector<float>& getAngles()
    {
        return angles;
    }
    
    const std::vector<float>& getAngles() const
    {
        return angles;
    }

    void add( const std::string& filename, const sf::Rect<int>& rect, unsigned count )
    {
        sf::Texture* texture = new sf::Texture;
        if( !texture->loadFromFile(filename, rect) )
        {
            throw std::invalid_argument("File does not exists\n");
        }

        textures.push_back(texture);

        sf::Sprite tmp;
        tmp.setTexture(*texture);
        //set origin by center
        tmp.setOrigin(rect.width / 2, rect.height / 2);

        for( size_t it{}; it < count; ++it )
        {
            tmp.setPosition(random(0, windowWidth), random(0, windowHeight));
            sprites.push_back(tmp);

            angles.emplace_back(getRadianFromDegree(random(0, 360)));
        }
    }
    
    template<typename FunctionType, typename... AdditionalParams>
    void update(FunctionType* updateFunc, AdditionalParams&&... params)
    {
        factor = speed * (timer.get_elapsed_time<tools::milliseconds>() / 10.f);
        updateFunc(*this, std::forward<AdditionalParams>(params)...);
    }

private:
    tools::Timer timer;
    float speed;
    float factor;
    std::pair<int,int> windowSize;
    
    int& windowWidth;
    int& windowHeight;
    
    std::vector<sf::Sprite> sprites;
    std::vector<float> angles;
    
    std::vector<sf::Texture*> textures;
};
/////////////////////////////////////////////////////////////////////////////////////////
class SimpleParticlesBuilder
{
public:

    SimpleParticlesBuilder()
        :
        data{},
        windowWidth{},
        windowHeight{},
        speed{10.f}
    {}


    static SimpleParticlesBuilder create()
    {
        return SimpleParticlesBuilder{};
    }

    SimpleParticlesBuilder& add( const std::tuple<std::string, sf::IntRect, unsigned>& newElement )
    {
        data.push_back(newElement);
        return *this;
    }

    SimpleParticlesBuilder& add( std::tuple<std::string, sf::IntRect, unsigned>&& newElement )
    {
        data.emplace_back(std::forward<decltype(newElement)>(newElement));
        return *this;
    }

    SimpleParticlesBuilder& add( const std::string& filename, const sf::IntRect& rect, const unsigned count )
    {
        data.emplace_back(std::make_tuple(filename, rect, count));
        return *this;
    }

    SimpleParticlesBuilder& setWindowParams( const int windowWidth, const int windowHeight )
    {
        this->windowWidth = windowWidth;
        this->windowHeight = windowHeight;
        return *this;
    }

    SimpleParticlesBuilder& setSpeed( const float speed )
    {
        this->speed = speed;
        return *this;
    }

    SimpleParticles build()
    {
        return SimpleParticles( std::move(data), windowWidth, windowHeight, speed );
    }
private:
    std::vector<std::tuple<std::string, sf::IntRect, unsigned>> data;
    int windowWidth;
    int windowHeight;
    float speed;
};
/////////////////////////////////////////////////////////////////////////////////////////
//
//    example using SimpleParticlesBuilder:
//
//      auto parts =
//          SimpleParticlesBuilder::create()
//            .add("img.png", sf::IntRect(0, 0, 32, 32), 33)
//            .setWindowParams(800, 600)
//            .setSpeed(10.f)
//            .build();
//
/////////////////////////////////////////////////////////////////////////////////////////
#endif //SIMPLE_PARTICLES
/////////////////////////////////////////////////////////////////////////////////////////