#include "field.hpp"
#include "screen.hpp"
#include "animation.hpp"
#include <cmath>
#include <iostream>
#include "gamerule.hpp"

uint8_t field_data[9];

extern sf::RenderWindow *app;
extern sf::Texture *mark_texture;

MouseField::MouseField(Field *field)
: m_field(field)
{
    auto screen = app->getSize();

    setMouseCatchOffset(sf::Vector2f((screen.x - 190)/2 + 10.f, (screen.y - 190)/2 + 10.f));
    setMouseCatchSize(sf::Vector2f(180.f, 180.f));
}

inline sf::Vector2i MouseField::getLocal(int& x, int& y)
{
    sf::Vector2u screen = app->getSize();
    sf::Vector2f basePos = m_field->m_base.getPosition();
    return sf::Vector2i(x - basePos.x, y - basePos.y);
}

inline size_t MouseField::localToCell(sf::Vector2i mousePos)
{
    return mousePos.y / m_field->m_cellSize * 3 + mousePos.x / m_field->m_cellSize;
}

void MouseField::onMouseMove(sf::Event& event)
{

    sf::Vector2i mouseLocal = getLocal(event.mouseMove.x, event.mouseMove.y);
    size_t cell_n = localToCell(mouseLocal);

    if (mouseLocal.x % 60 > 10 &&
        mouseLocal.y % 60 > 10)
    {
        m_field->highlight(cell_n);
    } else {
        m_field->mouseLeave();
    }

}

void MouseField::onMouseUp(sf::Event& event)
{
    sf::Vector2i mouseLocal = getLocal(event.mouseButton.x, event.mouseButton.y);
    size_t cell_n = localToCell(mouseLocal);

    if (mouseLocal.x % 60 > 10 &&
        mouseLocal.y % 60 > 10)
    {
        m_field->placeMark(cell_n);
    }
}

Field::Field(UI::Screen::Base *screen)
  : m_mouseField(this),
    m_prevHiglightCell(-1)
{
    sf::Vector2u dim = app->getSize();

    sf::RectangleShape sampleCell(sf::Vector2f(50.f, 50.f));


    m_cellSize = 60;
    sampleCell.move(sf::Vector2f((dim.x - 190)/2 + 10.f, (dim.y - 190)/2 + 10.f));

    m_base.setSize(sf::Vector2f(190.f, 190.f));
    m_base.setFillColor(sf::Color(255, 0, 0, 127));

    m_base.setPosition((dim.x - 190)/2, (dim.y - 190)/2);


    for (size_t i = 1; i < 10; i++)
    {
        m_cells.push_back(sampleCell);

        sampleCell.move(sf::Vector2f(60.f, 0.f));

        if (i % 3 == 0) sampleCell.move(sf::Vector2f(-180.f, 60.f));
    }

    screen->m_mouseEvtSub.subscribe(&m_mouseField);
}

void Field::Run()
{
    for (auto &ani : m_animations)
        ani->onTick();
}

bool xMark = true;

void Field::placeMark(size_t& cell)
{
    if (field_data[cell] != MARK_EMPTY)
        return;

    field_data[cell] = xMark ? MARK_CROSS : MARK_CIRCLE;

    sf::RectangleShape *mark = new sf::RectangleShape();

    mark->setTexture(mark_texture);
    mark->setTextureRect(sf::IntRect((xMark)?(0):(64), 0, 64, 64));
    mark->setSize(sf::Vector2f(30.f, 30.f));
    sf::Vector2f cellPos = m_cells[cell].getPosition();

    mark->setPosition(cellPos);
    mark->move(sf::Vector2f(10.f, 10.f));

    m_marks.push_back(mark);

    xMark = !xMark;
}

void Field::mouseLeave()
{
    for (auto &ani : m_animations) ani->play(sf::Color::White);
    m_prevHiglightCell = -1;
}

void Field::highlight(size_t& cell_n)
{
    if (m_prevHiglightCell == cell_n)
        return;

    m_prevHiglightCell = cell_n;

    FadeAnimation *animation = new FadeAnimation(&m_cells[cell_n], sf::seconds(.2f));
    animation->setInterrupt(true);

    animation->play(sf::Color(255, 201, 14));

    m_animations.push_back(animation);
}

void Field::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_base, states);

    for (auto &c : m_cells) target.draw(c, states);
    for (auto &m : m_marks) target.draw(*m, states);
}
