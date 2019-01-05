#ifndef CROSSZERO_MAINMENU_HPP
#define CROSSZERO_MAINMENU_HPP

#include "stdafx.hpp"
#include "button.hpp"
#include "ScreenManager.hpp"

extern Screen screen;

class MainMenu : public sf::Drawable, public sf::Transformable {
public:
    MainMenu(int _count);
    void update();
    ui::Button &operator[](const unsigned int &i);

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    ui::Button sampleBtn;
    int interval;
    std::vector<ui::Button> buttons;
};

#endif // CROSSZERO_MAINMENU_HPP
