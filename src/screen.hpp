#ifndef SCREEN_HPP
#define SCREEN_HPP

#include "simple_particles.hpp"
#include <SFML/Graphics.hpp>
#include "main_menu.hpp"
#include "animation.hpp"
#include "field.hpp"

enum ScreenLayerEnum {
    SCREEN_LAYER_BACKGROUND,
    SCREEN_LAYER_TOP,
    SCREEN_LAYER_OVERLAY
};

namespace UI {

namespace Screen {

class Base {
public:
    Base();
    void Hide();
    virtual int Run(sf::RenderWindow& app) = 0;
    void lostFocus();
    bool postEvent(sf::Event &evt);
    
    MouseEventSubject m_mouseEvtSub;
    bool m_mouseTroughOut;
};

//------------------------------------------------------------------------------

class ScreenManager {
public:
    ScreenManager() :screens{} {};
    
    void ChangeTo(Base * next, ScreenLayerEnum layer)
    {
        if (screens[layer] != nullptr) screens[layer]->Hide();
        screens[layer] = next;
    }
    
    void postEvent(sf::Event &evt)
    {
        size_t i = 2;
        
        switch (evt.type)
        {
        case sf::Event::MouseMoved:
        case sf::Event::MouseButtonPressed:
        case sf::Event::MouseButtonReleased:
            for (; i; i--) if (screens[i]->postEvent(evt)) break;
            while (i--) screens[i]->lostFocus();
        }
    }
    
    inline void Tick(sf::RenderWindow& app)
    {
        for (size_t i = 0; i < 3; i++) screens[i]->Run(app);
    }
    
private:
    Base *screens[3];
};

//------------------------------------------------------------------------------

class Background : public Base {
public:
    Background();
    int Run(sf::RenderWindow& app);
private:
    ::SimpleParticles parts;
    UI::Controls::Button btn;
};

//------------------------------------------------------------------------------

class TitleScreen : public Base {
public:
    TitleScreen();
    int Run(sf::RenderWindow& app);
    void Hide();
private:
    UI::Controls::Button button;
    sf::Text header;
    ::MainMenu menu;
};

//------------------------------------------------------------------------------

class LeaderBoard : public Base {
public:
    LeaderBoard();
    int Run(sf::RenderWindow& app);
private:
    sf::Text text;
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
    sf::Text version;
    sf::Clock clock;
    
    UI::Controls::Button btn;
};

} // namespace Screen

} // namespace UI

#endif // SCREEN_HPP
