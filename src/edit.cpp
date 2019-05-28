#include "edit.hpp"

namespace UI::Controls {

EditControl::EditControl()
{
    beam.setPosition(10, 10);   
    innerText.setString("Some text");
}

void EditControl::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(beam);
}

}
