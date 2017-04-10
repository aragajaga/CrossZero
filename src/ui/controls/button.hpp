#pragma once

#include "control.hpp"

namespace UI {
namespace Controls {

class Button : public Control {
public:
	Button();
	void setString(const sf::String& str);
	void update();
private:
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	std::wstring label;
	sf::RoundedRectangleShape base;
	sf::Text text;
};

}
}
