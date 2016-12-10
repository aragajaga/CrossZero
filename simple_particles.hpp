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

#include "timer.hpp"
/////////////////////////////////////////////////////////////////////////////////////////
class SimpleParticles
{

public:

    SimpleParticles(
        std::vector<std::tuple<std::string, sf::IntRect, unsigned>>&& data,
        int windowWidth,
        int windowHeight,
        int speed
    )
        :
        speed(speed),
        windowWidth(windowWidth),
        windowHeight(windowHeight),
        sprites{}
    {
        for( const auto& it : data )
            add(std::get<0>(it), std::get<1>(it), std::get<2>(it));
    }

    void setSpeed( const int speed )
    {
        this->speed = speed;
    }

    void setWindowParams( const int windowWidth, const int windowHeight )
    {
        this->windowWidth = windowWidth;
        this->windowHeight = windowHeight;

        for( auto& it : sprites )
        {
            it.setPosition(random(0, windowWidth), random(0, windowHeight));
        }
    }

    void add( const std::string& filename, const sf::Rect<int>& rect, unsigned count )
    {
        static std::vector<sf::Texture*> textures;

        sf::Texture* texture = new sf::Texture;
        if( !texture->loadFromFile(filename, rect) )
        {
            throw std::invalid_argument("File does not exists\n");
        }

        textures.push_back(texture);

        sf::Sprite tmp;
        tmp.setTexture(*texture);
        //adding alpha canal to color sprite
        sf::Color clr( tmp.getColor() );
        clr.a = 63;

        tmp.setColor(clr);
        //set origin by center
        tmp.setOrigin(rect.width / 2, rect.height / 2);

        for( size_t it{}; it < count; ++it )
        {
            tmp.setPosition(random(0, windowWidth), random(0, windowHeight));
            sprites.push_back(tmp);

            angles.emplace_back(static_cast<float>(random(0, 360) * 2 * PI / 360.f));
        }

    }

    const std::vector<sf::Sprite>& getSprites() const
    {
        return sprites;
    }

    void update()
    {
        float factor = speed * (timer.get_elapsed_time<tools::milliseconds>() / 10);
        for( size_t it{}; it < sprites.size(); ++it )
        {
            sprites[it].move(std::cos(angles[it]) * factor, std::sin(angles[it]) * factor);

            //check collision with walls
            if( sprites[it].getPosition().x - sprites[it].getOrigin().x < 0 )
            {
                angles[it] = PI - angles[it];
                sprites[it].setPosition(
                    sprites[it].getOrigin().x + 1,
                    sprites[it].getPosition().y
                );
            }
            if( sprites[it].getPosition().x + sprites[it].getOrigin().x > windowWidth )
            {
                angles[it] = PI - angles[it];
                sprites[it].setPosition(
                    windowWidth - sprites[it].getOrigin().x + 1,
                    sprites[it].getPosition().y
                );
            }
            if( sprites[it].getPosition().y - sprites[it].getOrigin().y < 0 )
            {
                angles[it] = -angles[it];
                sprites[it].setPosition(
                    sprites[it].getPosition().x,
                    sprites[it].getOrigin().y + 1
                );
            }
            if( sprites[it].getPosition().y + sprites[it].getOrigin().y > windowHeight )
            {
                angles[it] = -angles[it];
                sprites[it].setPosition(
                    sprites[it].getPosition().x,
                    windowHeight - sprites[it].getOrigin().y + 1
                );
            }

            sprites[it].rotate(1);
        }
        timer.restart();
    }

private:

    //simple random function
    float random( float from, float to )
    {
        static std::mt19937 gen( std::time(nullptr) );
        std::uniform_real_distribution<> dist( from, to );
        return dist(gen);
    }

    tools::Timer timer;
    int speed;
    int windowWidth;
    int windowHeight;
    std::vector<sf::Sprite> sprites;
    std::vector<float> angles;

    constexpr static float PI = 3.14159f;
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
        speed{10}
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

    SimpleParticlesBuilder& setSpeed( const int speed )
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
    int speed;
};
/////////////////////////////////////////////////////////////////////////////////////////
//
//    example using SimpleParticlesBuilder:
//
//      auto parts =
//          SimpleParticlesBuilder::create()
//            .add("img.png", sf::IntRect(0, 0, 32, 32), 33)
//            .setWindowParams(800, 600)
//            .setSpeed(10)
//            .build();
//
/////////////////////////////////////////////////////////////////////////////////////////
#endif //SIMPLE_PARTICLES
/////////////////////////////////////////////////////////////////////////////////////////
