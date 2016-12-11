#ifndef CROSSZERO_UI_CONTROL_HPP
#define CROSSZERO_UI_CONTROL_HPP

#include "stdafx.hpp"
#include "colorscheme.hpp"
#include "RoundedRectangleShape.hpp"

extern sf::Font arial;

namespace ui {

    class Control : public sf::Drawable, public sf::Transformable {
    public:
        virtual ~Control() {};
        virtual void setSize(const sf::Vector2f& size);
        virtual void setSize(const float& width, const float& height);
        virtual sf::Vector2f getSize() const;

        virtual void update() const;

    protected:
        sf::Vector2f m_size;
    };
}

#endif // CROSSZERO_UI_CONTROL_HPP
