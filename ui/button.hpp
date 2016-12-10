#ifndef CROSSZERO_UI_BUTTON_HPP
#define CROSSZERO_UI_BUTTON_HPP

#include "control.hpp"

namespace ui {

    class Button : public Control {
    public:
        Button();
        void setPosition(const sf::Vector2f& position);
        void setString(const sf::String& str);
        void setSize(const sf::Vector2f& size);
        sf::Vector2f getSize() const;

    private:
        void update();
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;

        std::wstring label;
        sf::Vector2f m_size;
        sf::Vector2f m_position;
        sf::RoundedRectangleShape base;
        sf::Text text;
    };
}

#endif // CROSSZERO_UI_BUTTON_HPP
