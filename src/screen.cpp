#include "screen.hpp"
#include "effects.hpp"
#include "shared_font.hpp"
#include "animation.hpp"

extern sf::RenderWindow* app;
// extern MouseEventSubject mouseSubject;

namespace UI {

namespace Screen {

void Base::Hide()
{
    // m_mouseEvtS.erase();
}

void Base::postEvent(sf::Event &evt)
{
    for (auto &sub : m_mouseEvtSub.m_observers)
    {
        m_mouseEvtSub.fire(evt);
    }
}

//------------------------------------------------------------------------------

Background::Background()
: parts(SimpleParticlesBuilder::create()
        .add("res/xo.png", sf::IntRect(0, 0, 24, 24), 10)
        .add("res/xo.png", sf::IntRect(24, 0, 24, 24), 10)
        .setSpeed(0.5f)
        .setWindowParams(800, 600)
        .build())
{}

int Background::Run(sf::RenderWindow& app)
{
    parts.setWindowParams(app.getSize().x, app.getSize().y);
    parts.update(box);

    app.clear();
    for (const auto& it: parts.getSprites())
        app.draw(it);
    return 0;
}

//------------------------------------------------------------------------------

TitleScreen::TitleScreen()
: menu(::MainMenu(this))
{
    header.setFont(SharedFont::getInstance().font);
    header.setString("CrossZero");
    header.setFillColor(sf::Color::White);

    #ifdef DEBUG
    version.setFont(SharedFont::getInstance().font);
    version.setString("Debug build");
    version.setCharacterSize(24);
    version.setFillColor(sf::Color::White);
    version.setOutlineColor(sf::Color::Black);
    version.setOutlineThickness(1.f);
    #endif

    #ifdef DEBUG
    std::cout << "[TitleScreen] Constructed" << std::endl;
    #endif
}

int TitleScreen::Run(sf::RenderWindow& app)
{
    header.setCharacterSize(app.getSize().y * 72 / 480);
    header.setPosition(
        (app.getSize().x - header.getLocalBounds().width) / 2,
        app.getSize().y * (72 - 21) / 480
    );

    version.setPosition(
        app.getSize().x - version.getLocalBounds().width - 10,
        10
    );

    menu.update(app);

    for (auto& anim : animations)
            anim->onTick();

    app.draw(header);
    #ifdef DEBUG
    app.draw(version);
    #endif
    app.draw(menu);

    return 0;
}

//------------------------------------------------------------------------------

GameScreen::GameScreen()
: field()
{

}

int GameScreen::Run(sf::RenderWindow& app)
{
    app.draw(field);
    
    return 0;
}

//------------------------------------------------------------------------------

LoadingScreen::LoadingScreen()
{
    auto screen = app->getSize();
    
    spin.setSize(sf::Vector2f(50.f, 50.f));
    spin.setOrigin(sf::Vector2f(25.f, 25.f));
    spin.setPosition(sf::Vector2f(screen.x/2.f, screen.y/2.f));
    
    text.setFont(SharedFont::getInstance().font);
    text.setString("Loading...");
    text.setCharacterSize(24);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(1.f);
    
    text.setPosition(sf::Vector2f((screen.x - text.getLocalBounds().width)/2.f,
        (screen.y - text.getLocalBounds().height)/2.f + 75.f));
}

int LoadingScreen::Run(sf::RenderWindow& app)
{
    spin.rotate(5.f);
    
    app.draw(spin);
    app.draw(text);
    return 0;
}

//------------------------------------------------------------------------------

FPSCounter::FPSCounter()
{
    fps.setFont(SharedFont::getInstance().font);
    fps.setPosition(10.f, 10.f);
    fps.setCharacterSize(24);
    fps.setOutlineColor(sf::Color::Black);
    fps.setOutlineThickness(1.f);
}

int FPSCounter::Run(sf::RenderWindow& app)
{
    fps.setString("fps: " + std::to_string(
        static_cast<int>(1000.f/clock.restart().asMilliseconds()))
    );
    app.draw(fps);
    return 0;
}

}

}
