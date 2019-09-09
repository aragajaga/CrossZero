#include "screen.hpp"
#include "effects.hpp"
#include "shared_font.hpp"
#include "animation.hpp"

namespace UI {

namespace Screen {

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
: menu(::MainMenu())
{
    header.setFont(SharedFont::getInstance().font);
    header.setString("CrossZero");
    header.setFillColor(sf::Color::White);

    version.setFont(SharedFont::getInstance().font);
    version.setString("Some text in top-right corner.");
    version.setCharacterSize(24);
    version.setFillColor(sf::Color::White);
    version.setOutlineColor(sf::Color::Black);
    version.setOutlineThickness(1.f);

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
    app.draw(version);
    app.draw(menu);

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
