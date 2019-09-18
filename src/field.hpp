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
    sf::Vector2i getLocal(int& x, int& y);
    size_t localToCell(sf::Vector2i mouse);
    void onMouseUp(sf::Event& event);
    void onMouseMove(sf::Event& event);
    Field *m_field;
};

class Field : public sf::RectangleShape {
    friend class MouseField;

public:
    Field(UI::Screen::Base* screen);
    void highlight(uint8_t& cell_n);
    void Run();
    void mouseLeave();
    void placeMark(uint8_t& cell);

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    std::vector<FadeAnimation *> m_animations;
    std::vector<sf::RectangleShape> m_cells;
    std::vector<sf::RectangleShape *> m_marks;

    int m_prevHiglightCell;
    int m_cellSize;
    sf::RectangleShape m_base;
    MouseField m_mouseField;
};

#endif // FIELD_HPP
