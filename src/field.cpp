#include "field.hpp"

uint8_t field_data[9];

extern sf::RenderWindow *app;

Field::Field()
{
    sf::RectangleShape sampleCell(sf::Vector2f(50.f, 50.f));
    
    
    auto screen = app->getSize();
    
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
}
