#ifndef FIELD_HPP
#define FIELD_HPP

#include "mouse_event.hpp"


extern uint8_t field_data[9];

class MouseField : public MouseEventObserver {
public:
    MouseField();
    void onMouseEnter();
    void onMouseLeave();
};

class Field : public sf::RectangleShape {
public:
    Field();

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    std::vector<sf::RectangleShape> cells;
    sf::RectangleShape base;
    
    sf::RectangleShape mark;
    sf::RectangleShape mark2;
};

#endif // FIELD_HPP
