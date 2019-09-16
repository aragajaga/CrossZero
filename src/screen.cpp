#include "screen.hpp"
#include "effects.hpp"
#include "shared_font.hpp"
#include "animation.hpp"

extern sf::RenderWindow* app;
extern sf::Font *font_system;
// extern MouseEventSubject mouseSubject;

namespace UI {

namespace Screen {

Base::Base()
: m_mouseTroughOut{false} {}

void Base::Hide()
{
    // m_mouseEvtS.erase();
}

bool Base::postEvent(sf::Event &evt)
{
    bool affected;
    
    for (auto &sub : m_mouseEvtSub.m_observers)
        if (m_mouseEvtSub.fire(evt))
            affected = true;
    
    return affected;
}

void Base::lostFocus()
{
    m_mouseEvtSub.lostFocus();
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

    app.clear(sf::Color(239, 228, 176, 255));
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
    header.setFillColor(sf::Color::Black);

    button.setInitialPos(sf::Vector2f(20.f, 20.f));
    button.setInitialSize(sf::Vector2f(200.f, 50.f));
    button.setString("Test");
    
    m_mouseEvtSub.m_observers.push_back(&button);

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

    menu.update();

    for (auto& anim : animations)
        anim->onTick();

    app.draw(header);
    app.draw(menu);
    app.draw(button);

    return 0;
}

//------------------------------------------------------------------------------

LeaderBoard::LeaderBoard()
{
    text.setFont(SharedFont::getInstance().font);
    text.setString("Not implemented yet. Check back later.");
    text.setFillColor(sf::Color::White);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(1.f);
}

int LeaderBoard::Run(sf::RenderWindow& app)
{
    text.setPosition(
        (app.getSize().x - text.getLocalBounds().width) / 2,
        (app.getSize().y - text.getLocalBounds().height) / 2
    );

    app.draw(text);
}

//------------------------------------------------------------------------------

GameScreen::GameScreen()
: field(this)
{}

int GameScreen::Run(sf::RenderWindow& app)
{
    field.Run();
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
    fps.setFont(*font_system);
    fps.setPosition(10.f, 10.f);
    fps.setCharacterSize(24);
    fps.setOutlineColor(sf::Color::Black);
    fps.setOutlineThickness(1.f);
    
    #ifdef DEBUG
    version.setFont(*font_system);
    version.setString("Debug build");
    version.setCharacterSize(24);
    version.setFillColor(sf::Color::White);
    version.setOutlineColor(sf::Color::Black);
    version.setOutlineThickness(1.f);
    #endif
    
    btn.setInitialPos(sf::Vector2f(10.f, 10.f));
    btn.setInitialSize(sf::Vector2f(200.f, 50.f));
    btn.setString("Test");
    
    m_mouseEvtSub.m_observers.push_back(&btn);
}

int FPSCounter::Run(sf::RenderWindow& app)
{
    for (auto& anim : animations)
        anim->onTick();
    
    fps.setString("fps: " + std::to_string(
        static_cast<int>(1000.f/clock.restart().asMilliseconds()))
    );
    
    version.setPosition(
        app.getSize().x - version.getLocalBounds().width - 10,
        10
    );
    
    app.draw(btn);
    app.draw(fps);
    #ifdef DEBUG
    app.draw(version);
    #endif
    return 0;
}

}

}
