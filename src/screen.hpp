#ifndef SCREEN_HPP
#define SCREEN_HPP

#include "simple_particles.hpp"
#include <SFML/Graphics.hpp>
#include "main_menu.hpp"
#include "animation.hpp"
#include "field.hpp"

namespace UI {

namespace Screen {

class Base {
public:
    virtual int Run(sf::RenderWindow& app) = 0;
};

//------------------------------------------------------------------------------

class Background : public Base {
public:
    Background();
    int Run(sf::RenderWindow& app);
private:
    ::SimpleParticles parts;
};

//------------------------------------------------------------------------------

class TitleScreen : public Base {
public:
    TitleScreen();
    int Run(sf::RenderWindow& app);
private:
    sf::Text header;
    sf::Text version;
    ::MainMenu menu;
};

//------------------------------------------------------------------------------

class GameScreen : public Base {
public:
    GameScreen();
    int Run(sf::RenderWindow& app);
private:
    Field field;
};

//------------------------------------------------------------------------------

class FPSCounter : public Base {
public:
    FPSCounter();
    int Run(sf::RenderWindow& app);
private:
    sf::Text fps;
    sf::Clock clock;
};

} // namespace Screen

} // namespace UI

#endif // SCREEN_HPP
