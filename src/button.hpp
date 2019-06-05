#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "mouse_event.hpp"
#include "control.hpp"
#include "animation.hpp"

namespace UI {
namespace Controls {

class Button : public sf::RectangleShape, public MouseEventObserver {
public:
	Button();
	void setString(const sf::String& str);
	void update();
    void setPosition(float x, float y);
    void setPosition(sf::Vector2f pos);
    void setSize(float x, float y);
    void setSize(sf::Vector2f size);
    void setFillColor(sf::Color color);
    
    void onMouseEnter();
    void onMouseLeave();
    void onMouseClick();
    void onMouseUp();
    
    FadeAnimation fadeInAnim;
    FadeAnimation fadeOutAnim;
    
    sf::Color hoverColor;
    sf::Color normalColor;
private:
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	std::wstring label;
	sf::RoundedRectangleShape base;
	sf::Text text;
};

}
}

#endif // BUTTON_HPP
