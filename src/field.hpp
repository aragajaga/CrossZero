#ifndef FIELD_HPP
#define FIELD_HPP

#include "mouse_event.hpp"

extern uint8_t field_data[9];

class Field : public sf::RectangleShape, public MouseEventObserver {
public:
    Field();

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    std::vector<sf::RectangleShape> cells;
    sf::RectangleShape base;
};

#endif // FIELD_HPP
