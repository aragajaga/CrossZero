#ifndef SCREEN_HPP
#define SCREEN_HPP

#include "UI/simple_particles.hpp"
#include <SFML/Graphics.hpp>
#include "UI/main_menu.hpp"

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

class MainMenu : public Base {
public:
    MainMenu();
    int Run(sf::RenderWindow& app);
private:
    sf::Text header;
    sf::Text version;
    ::MainMenu mainMenu;
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

//------------------------------------------------------------------------------

class Settings : public Base {
public:
    Settings();
    int Run(sf::RenderWindow& app);
public:
    sf::Text splash;
};

} // namespace Screen

} // namespace UI

#endif // SCREEN_HPP
