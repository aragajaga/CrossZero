#ifndef SCREEN_HPP
#define SCREEN_HPP

#include "simple_particles.hpp"
#include <SFML/Graphics.hpp>
#include "main_menu.hpp"
#include "animation.hpp"
#include "field.hpp"

enum ScreenLayerEnum {
    SCREEN_LAYER_BACKGROUND,
    SCREEN_LAYER_TOP
};

namespace UI {

namespace Screen {

class Base {
public:
    virtual int Run(sf::RenderWindow& app) = 0;
    void Hide();
};

//------------------------------------------------------------------------------

class ScreenManager {
public:
    ScreenManager() :screens{} {};
    
    void ChangeTo(Base * next, ScreenLayerEnum layer)
    {
        if (screens[layer] != nullptr)
            screens[layer]->Hide();
        screens[layer] = next;
    }
    
    inline void Tick(sf::RenderWindow& app)
    {
        screens[0]->Run(app);
        screens[1]->Run(app);
    }
    
private:
    Base *screens[2];
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
    void Hide();
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

class LoadingScreen : public Base {
public:
    LoadingScreen();
    int Run(sf::RenderWindow& app);
private:
    sf::Clock clock;
    sf::RectangleShape spin;
    sf::Text text;
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
