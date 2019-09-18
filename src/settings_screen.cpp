#include "settings_screen.hpp"
#include "shared_font.hpp"

namespace UI::Screen {

Settings::Settings()
{
    splash.setFont(SharedFont::getInstance().font);
    splash.setString("Settings");
    splash.setOutlineColor(sf::Color::Black);
    splash.setOutlineThickness(1.f);
    splash.setFillColor(sf::Color::White);

    field.setSize(sf::Vector2f(100, 40));
}

int Settings::Run(sf::RenderWindow& app)
{
    splash.setPosition(
        (app.getSize().x - splash.getLocalBounds().width) / 2,
        (app.getSize().y - splash.getLocalBounds().height) / 2
    );

    app.draw(splash);
    app.draw(field);

    return 0;
}

} // namespace UI::Screen
