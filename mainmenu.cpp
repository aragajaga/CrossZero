#include "mainmenu.hpp"

extern Screen screen;

MainMenu::MainMenu(int _count)
{
    sampleBtn.setSize( sf::Vector2f(200.f, 50.f) );

    buttons.resize(_count);
    int i = 0;
    // TODO: Чем заменить итератор
    for ( auto& num : buttons ) {
        num = sampleBtn;
        num.setString( std::to_wstring(i) );
        num.setPosition( sf::Vector2f( 10.f, 40.f*i ) );
        ++i;
    }
}

void MainMenu::update()
{
    int i = 0;
    for ( auto& num : buttons ) {
        num.setPosition( sf::Vector2f( (screen.getWnd()->getSize().x - screen.getWnd()->getSize().y * (sampleBtn.getSize().y/480.f)*4 )/2,
                                       ( screen.getWnd()->getSize().y - screen.getWnd()->getSize().y * sampleBtn.getSize().y/480.f*buttons.size() )/2 + screen.getWnd()->getSize().y*(sampleBtn.getSize().y+10)/480.f*i ));
        num.setSize( sf::Vector2f( screen.getWnd()->getSize().y * (sampleBtn.getSize().y / 480.f)*4, screen.getWnd()->getSize().y * (sampleBtn.getSize().y / 480.f) ) );
        ++i;
    }
}

ui::Button& MainMenu::operator[](const unsigned int& i)
{
    return buttons.at(i);
}

void MainMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for ( auto& num : buttons ) {
        target.draw(num, states);
    }
}
