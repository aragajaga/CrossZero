#ifndef FIELD_HPP
#define FIELD_HPP

#include "mouse_event.hpp"
#include "animation.hpp"


extern uint8_t field_data[9];

namespace UI::Screen
{
    class Base;
}

class Field;

class MouseField : public MouseEventObserver {
public:
    MouseField(Field *field);
    size_t localToCell(sf::Vector2i mouse);
    void onMouseUp();
    void onMouseMove();
    Field *m_field;
};

class Field : public sf::RectangleShape {
public:
    Field(UI::Screen::Base* screen);
    void highlight(size_t cell_n);
    void Run();
    void mouseLeave();
    void placeMark(size_t cell);
private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    std::vector<sf::RectangleShape> cells;
    sf::RectangleShape base;

    sf::RectangleShape mark;
    sf::RectangleShape mark2;

    MouseField m_mouseField;

    int m_prevHiglightCell;
    std::vector<FadeAnimation *> m_animations;
    std::vector<sf::RectangleShape *> m_marks;
};

#endif // FIELD_HPP
