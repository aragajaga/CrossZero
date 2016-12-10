#include "button.hpp"

namespace ui {

    Button::Button()
    {
        base.setCornersRadius(2.f);
        base.setCornerPointCount(4);
        base.setFillColor(Color::cocoaLight);

        text.setFont(arial);
        text.setString("< Unnamed Item >");
        text.setFillColor(Color::cocoaMilk);
    }

    void Button::setPosition(const sf::Vector2f& position)
    {
        m_position = position;
        update();
    }


    void Button::setSize(const sf::Vector2f& size)
    {
        m_size = size;
        update();
    }

    void Button::setString(const sf::String& str)
    {
        text.setString(str);
        update();
    }

    sf::Vector2f Button::getSize() const
    {
        return m_size;
    }

    void Button::update()
    {
        base.setSize( m_size );
        base.setPosition( m_position.x, m_position.y );
        sf::FloatRect textBounds = text.getLocalBounds();
        float textCharacterSize = m_size.y*0.48f;
        text.setCharacterSize( textCharacterSize );
        text.setPosition(m_position.x + m_size.x/2.f - textBounds.width/2.f, m_position.y + m_size.y/2.f - textCharacterSize/2.f);
    }

    void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        target.draw( base, states );
        target.draw( text, states );
    }
}
