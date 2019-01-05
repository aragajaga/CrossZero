#include "control.hpp"

namespace ui {

    void Control::setSize(const sf::Vector2f& size)
    {
        m_size = size;
        update();
    }

    void Control::setSize(const float& width, const float& height)
    {
        m_size = sf::Vector2f(width, height);
        update();
    }

    sf::Vector2f Control::getSize() const
    {
        return m_size;
    }

    void Control::update() const
    {

    }
}
