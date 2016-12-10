#ifndef CROSSZERO_UI_CONTROL_HPP
#define CROSSZERO_UI_CONTROL_HPP

#include "stdafx.hpp"
#include "colorscheme.hpp"
#include "RoundedRectangleShape.hpp"

extern sf::Font arial;

namespace ui {

    class Control : public sf::Drawable, public sf::Transformable {};;
}

#endif // CROSSZERO_UI_CONTROL_HPP
