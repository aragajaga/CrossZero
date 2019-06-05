#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include "stdafx.hpp"
#include "button.hpp"

class MainMenu : public sf::Drawable, public sf::Transformable {
public:
    MainMenu();
    void update(sf::RenderWindow& app);

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    std::vector<UI::Controls::Button *> buttons;
};

#endif // MAIN_MENU_HPP
