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
        update();
    }

    void Button::setString(const sf::String& str)
    {
        text.setString(str);
        update();
    }

    void Button::update()
    {
        base.setSize( m_size );
        base.setCornersRadius( m_size.y*2/50.f );

        sf::FloatRect textBounds = text.getLocalBounds();
        float textCharacterSize = m_size.y*0.48f;
        text.setCharacterSize( textCharacterSize );
        text.setPosition(m_size.x/2.f - textBounds.width/2.f, m_size.y/2.f - (textCharacterSize/2.f + m_size.y*3/50) );
    }

    void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        states.transform = getTransform();
        target.draw( base, states );
        target.draw( text, states );
    }
}
