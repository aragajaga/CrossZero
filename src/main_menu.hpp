#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include "stdafx.hpp"
#include "button.hpp"

class MainMenu : public sf::Drawable, public sf::Transformable {
public:
    MainMenu(int _count);
    void update(sf::RenderWindow& app);
    UI::Controls::Button &operator[](const unsigned int &i);

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    UI::Controls::Button sampleBtn;
    int interval;
    std::vector<UI::Controls::Button> buttons;
};

#endif // MAIN_MENU_HPP
