#ifndef CROSSZERO_UI_BUTTON_HPP
#define CROSSZERO_UI_BUTTON_HPP

#include "control.hpp"

namespace ui {

    class Button : public Control {
    public:
        Button();
        void setString(const sf::String& str);
        void update();

    private:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;

        std::wstring label;
        sf::RoundedRectangleShape base;
        sf::Text text;
    };
}

#endif // CROSSZERO_UI_BUTTON_HPP