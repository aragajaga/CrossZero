#pragma once

#include "stdafx.hpp"
#include "controls/button.hpp"

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
