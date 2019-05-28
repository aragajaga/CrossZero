#ifndef SETTINGS_SCREEN_HPP
#define SETTINGS_SCREEN_HPP

#include "screen.hpp"
#include "edit.hpp"

namespace UI::Screen {

class Settings : public Base {
public:
    Settings();
    int Run(sf::RenderWindow& app);
private:
    UI::Controls::EditControl field;
    sf::Text splash;
};

} // namespace UI::Screen

#endif // SETTINGS_SCREEN_HPP
