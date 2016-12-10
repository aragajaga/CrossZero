#ifndef CROSSZERO_SCREENMANAGER_HPP
#define CROSSZERO_SCREENMANAGER_HPP

#include "stdafx.hpp"

class Screen
{
public:
    void setWnd(sf::RenderWindow* _wnd)
    {
        wnd = _wnd;
    }

    sf::RenderWindow* getWnd() const
    {
        return wnd;
    };


private:
    sf::RenderWindow* wnd;
};

#endif // CROSSZERO_SCREENMANAGER_HPP
