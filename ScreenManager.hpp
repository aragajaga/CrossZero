#ifndef CROSSZERO_SCREENMANAGER_HPP
#define CROSSZERO_SCREENMANAGER_HPP

#include <SFML/Graphics.hpp>

class ScreenManager
{
public:
    ScreenManager( sf::RenderWindow &_wnd ) : wnd(_wnd) {};

    float calcRelativeByX( const float &value ) const;
    float calcRelativeByY( const float &value ) const;

    float getPxMenuVMargin();

private:
    float menuVMargin = .15f;
    sf::RenderWindow& wnd;
};

#endif // CROSSZERO_SCREENMANAGER_HPP