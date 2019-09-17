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

size_t MouseField::localToCell(sf::Vector2i mousePos)
{
    return std::floor(mousePos.y / 60.f) * 3 + std::floor(mousePos.x/60.f); 
}

void MouseField::onMouseMove()
{
    auto screen = app->getSize();
    
    sf::Vector2f basePos = sf::Vector2f((screen.x - 190)/2, (screen.y - 190)/2);
    sf::Vector2i mouse = sf::Mouse::getPosition(*app);
    std::cout << "[MOUSE GLOBAL] x:" << mouse.x << " y:" << mouse.y << std::endl;
    
    sf::Vector2i mouseLocal = sf::Vector2i(mouse.x - basePos.x, mouse.y - basePos.y);
    std::cout << "[MOUSE LOCAL] x:" << mouseLocal.x << " y:" << mouseLocal.y << std::endl;
    
    size_t cell_n = localToCell(mouseLocal);
    
    if ((mouseLocal.x % 60) > 10 && mouseLocal.y % 60 > 10)
    {
        m_field->highlight(cell_n);
        #ifdef DEBUG
        std::cout << "[CELL] " << (int)cell_n << std::endl;
        #endif
    } else {
        m_field->mouseLeave();
    }
    
}

void MouseField::onMouseUp()
{
    auto screen = app->getSize();
    
    sf::Vector2f basePos = sf::Vector2f((screen.x - 190)/2, (screen.y - 190)/2);
    sf::Vector2i mouse = sf::Mouse::getPosition(*app);
    std::cout << "[MOUSE GLOBAL] x:" << mouse.x << " y:" << mouse.y << std::endl;
    
    sf::Vector2i mouseLocal = sf::Vector2i(mouse.x - basePos.x, mouse.y - basePos.y);
    std::cout << "[MOUSE LOCAL] x:" << mouseLocal.x << " y:" << mouseLocal.y << std::endl;
    
    size_t cell_n = localToCell(mouseLocal);
    
    if (mouseLocal.x % 60 > 10 &&
        mouseLocal.y % 60 > 10)
    {
        m_field->placeMark(cell_n);
        #ifdef DEBUG
        std::cout << "[CELL CLICK] " << (int)cell_n << std::endl;
        #endif
    }
}

Field::Field(UI::Screen::Base *screen)
: mark(), mark2(), m_mouseField(this), m_prevHiglightCell(-1)
{   
    sf::RectangleShape sampleCell(sf::Vector2f(50.f, 50.f));
    
    auto dim = app->getSize();
    
    mark.setTexture(mark_texture);
    mark.setTextureRect(sf::IntRect(0, 0, 64, 64));
    mark.setSize(sf::Vector2f(30.f, 30.f));
    mark.setPosition(sf::Vector2f((dim.x - 190)/2 + 20.f, (dim.y - 190)/2 + 20.f));
    
    mark2.setTexture(mark_texture);
    mark2.setTextureRect(sf::IntRect(64, 0, 64, 64));
    mark2.setSize(sf::Vector2f(30.f, 30.f));
    mark2.setPosition(sf::Vector2f((dim.x - 190)/2 + 80.f, (dim.y - 190)/2 + 80.f));
    
    sampleCell.move(sf::Vector2f((dim.x - 190)/2 + 10.f, (dim.y - 190)/2 + 10.f));
    
    base.setSize(sf::Vector2f(190.f, 190.f));
    base.setFillColor(sf::Color(255, 0, 0, 127));
    
    base.setPosition((dim.x - 190)/2, (dim.y - 190)/2);
    
    
    for (size_t i = 1; i < 10; i++)
    {
        cells.push_back(sampleCell);
        
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

void Field::placeMark(size_t cell)
{
    if (field_data[cell] != MARK_EMPTY)
        return;
    
    field_data[cell] = xMark ? MARK_CROSS : MARK_CIRCLE;
    
    sf::RectangleShape *mark = new sf::RectangleShape();
    
    mark->setTexture(mark_texture);
    mark->setTextureRect(sf::IntRect((xMark)?(0):(64), 0, 64, 64));
    mark->setSize(sf::Vector2f(30.f, 30.f));
    sf::Vector2f cellPos = cells[cell].getPosition();
    
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

void Field::highlight(size_t cell_n)
{
    if (m_prevHiglightCell == cell_n)
        return;
    
    m_prevHiglightCell = cell_n;
    
    FadeAnimation *animation = new FadeAnimation(&cells[cell_n], sf::seconds(.2f));
    animation->setInterrupt(true);
    
    for (auto &ani : m_animations) ani->play(sf::Color::White);
    
    animation->play(sf::Color(255, 201, 14));
    
    m_animations.push_back(animation);
}

void Field::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(base, states);
    
    for (auto &c : cells) target.draw(c, states);
    for (auto &m : m_marks) target.draw(*m, states);
}
