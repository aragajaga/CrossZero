#include "screen.hpp"
#include "effects.hpp"
#include "shared_font.hpp"

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
: menu(::MainMenu(3))
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
}

sf::Color mix(sf::Color a, sf::Color b, float alpha)
{
    a.r = (a.r * alpha) + (b.r * (1.f - alpha));
    a.g = (a.g * alpha) + (b.g * (1.f - alpha));
    a.b = (a.b * alpha) + (b.b * (1.f - alpha));
    return a;
};

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

    menu[0].setString("Play");
    menu[1].setString("Leaderboard");
    menu[2].setString("Settings");
    menu.update(app);

    for (size_t i = 0; i < 3; i++)
    {
        auto btn = &menu[i];
        if (btn->fadeInAnim.isPlaying())
        {
            float delta = btn->fadeInAnim.getElapsed().asSeconds() / .5f;
            
            if (delta > 1.f)
                btn->fadeInAnim.stop();
            else
                btn->setFillColor(mix(btn->hoverColor, btn->normalColor,
                        delta));
        } else if (btn->fadeOutAnim.isPlaying())
        {
            float delta = btn->fadeOutAnim.getElapsed().asSeconds() / .5f;
            
            if (delta > 1.f)
                btn->fadeOutAnim.stop();
            else
                btn->setFillColor(mix(btn->normalColor, btn->hoverColor,
                        delta));
        }
        
        app.draw(*btn);
    }

    app.draw(header);
    app.draw(version);

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
