#include "field.hpp"

uint8_t field_data[9];

extern sf::RenderWindow *app;
extern sf::Texture *mark_texture;

MouseField::MouseField()
{
    auto screen = app->getSize();
    
    setMouseCatchOffset(sf::Vector2f((screen.x - 190)/2, (screen.y - 190)/2));
    setMouseCatchSize(sf::Vector2f(190.f, 190.f));
}

void MouseField::onMouseEnter()
{
    sf::Vector2i mouse = sf::Mouse::getPosition();
}

void MouseField::onMouseLeave()
{
}

Field::Field()
: mark(), mark2()
{
    sf::RectangleShape sampleCell(sf::Vector2f(50.f, 50.f));
    
    auto screen = app->getSize();
    
    mark.setTexture(mark_texture);
    mark.setTextureRect(sf::IntRect(0, 0, 64, 64));
    mark.setSize(sf::Vector2f(30.f, 30.f));
    mark.setPosition(sf::Vector2f((screen.x - 190)/2 + 20.f, (screen.y - 190)/2 + 20.f));
    
    mark2.setTexture(mark_texture);
    mark2.setTextureRect(sf::IntRect(64, 0, 64, 64));
    mark2.setSize(sf::Vector2f(30.f, 30.f));
    mark2.setPosition(sf::Vector2f((screen.x - 190)/2 + 80.f, (screen.y - 190)/2 + 80.f));
    
    sampleCell.move(sf::Vector2f((screen.x - 190)/2 + 10.f, (screen.y - 190)/2 + 10.f));
    
    base.setSize(sf::Vector2f(190.f, 190.f));
    base.setFillColor(sf::Color(255, 0, 0, 127));
    
    base.setPosition((screen.x - 190)/2, (screen.y - 190)/2);
    
    
    for (size_t i = 1; i < 10; i++)
    {
        cells.push_back(sampleCell);
        
        sampleCell.move(sf::Vector2f(60.f, 0.f));
        
        if (i % 3 == 0) sampleCell.move(sf::Vector2f(-180.f, 60.f));
    }
}

void Field::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(base, states);
    
    for (auto &c : cells)
    {
        target.draw(c, states);
    }
    
    target.draw(mark, states);
    target.draw(mark2, states);
}
