#ifndef CONTROL_HPP
#define CONTROL_HPP

#include "stdafx.hpp"
#include "color_scheme.hpp"
#include "rounded_rectangle.hpp"

namespace UI {
namespace Controls {

class Control : public sf::Drawable, public sf::Transformable {
public:
    virtual ~Control() {}
    virtual void setSize(const sf::Vector2f& size);
    virtual void setSize(const float& width, const float& height);
    virtual sf::Vector2f getSize() const;

    virtual void update() const;

protected:
    sf::Vector2f m_size;
};

}
}

#endif // CONTROL_HPP
