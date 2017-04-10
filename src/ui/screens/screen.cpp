#include "screen.hpp"
#include "UI/effects.hpp"
#include "UI/shared_font.hpp"

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

    app.clear(sf::Color::Red);
	for (const auto& it: parts.getSprites())
        app.draw(it);
	return 0;
}

//------------------------------------------------------------------------------

MainMenu::MainMenu()
: mainMenu(::MainMenu(3))
{
    header.setFont(SharedFont::getInstance().font);
    header.setString("CrossZero");
    header.setFillColor(sf::Color::White);

    version.setFont(SharedFont::getInstance().font);
    version.setString("0.2.0a");
    version.setCharacterSize(24);
    version.setFillColor(sf::Color::White);
    version.setOutlineColor(sf::Color::Black);
    version.setOutlineThickness(1.f);
}

int MainMenu::Run(sf::RenderWindow& app)
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

    mainMenu[0].setString("Play");
    mainMenu[1].setString("Leaderboard");
    mainMenu[2].setString("Settings");
    mainMenu.update(app);

    app.draw(header);
    app.draw(version);
    app.draw(mainMenu);

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

//------------------------------------------------------------------------------

Settings::Settings()
{
    bletZabylSlovo_OTREFACTORIT_SROCHNA.setFont(SharedFont::getInstance().font);
    bletZabylSlovo_OTREFACTORIT_SROCHNA.setString("UI::Screen::Settings");
    bletZabylSlovo_OTREFACTORIT_SROCHNA.setOutlineColor(sf::Color::Black);
    bletZabylSlovo_OTREFACTORIT_SROCHNA.setOutlineThickness(1.f);
    bletZabylSlovo_OTREFACTORIT_SROCHNA.setFillColor(sf::Color::White);
}

Settings::Run(sf::RenderWindow& app)
{
    bletZabylSlovo_OTREFACTORIT_SROCHNA.setPosition(
        (app.getSize().x - bletZabylSlovo_OTREFACTORIT_SROCHNA.getLocalBounds().width) / 2,
        (app.getSize().y - bletZabylSlovo_OTREFACTORIT_SROCHNA.getLocalBounds().height) / 2
    );

    app.draw(bletZabylSlovo_OTREFACTORIT_SROCHNA);
}

}

}
