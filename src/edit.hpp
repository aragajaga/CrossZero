#ifndef EDIT_HPP
#define EDIT_HPP

#include "control.hpp"

namespace UI::Controls {

class EditControl : public Control {
public:
    EditControl();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
    sf::RectangleShape beam;
    sf::Text innerText;
};

}

#endif // EDIT_HPP
