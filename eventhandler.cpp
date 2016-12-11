#include "eventhandler.hpp"

void EventHandler::push(const ui::Control& obj_)
{
    objects.push_back(obj_);
}

void EventHandler::poll(const sf::Event& event)
{
    for (auto &obj : objects) {
        if (event.mouseButton.x >= obj.get().getPosition().x && event.mouseButton.x <= obj.get().getPosition().x+obj.get().getSize().x &&
            event.mouseButton.y >= obj.get().getPosition().y && event.mouseButton.y <= obj.get().getPosition().y+obj.get().getSize().y)
        {
            std::cout << "Pressed" << std::endl;
        }
    }
}
