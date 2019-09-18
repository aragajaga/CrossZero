#include "animation.hpp"

sf::Color mix(sf::Color a, sf::Color b, float alpha)
{
    a.r = (a.r * alpha) + (b.r * (1.f - alpha));
    a.g = (a.g * alpha) + (b.g * (1.f - alpha));
    a.b = (a.b * alpha) + (b.b * (1.f - alpha));
    return a;
}
