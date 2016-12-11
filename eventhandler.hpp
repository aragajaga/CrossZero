#ifndef CROSSZERO_EVENTHANDLER_HPP
#define CROSSZERO_EVENTHANDLER_HPP

#include <stdafx.hpp>
#include "ui/control.hpp"

class EventHandler {
public:
    void push(const ui::Control& obj_);
    void poll(const sf::Event& event);

private:
    std::vector< std::reference_wrapper<const ui::Control> > objects;
};

#endif // CROSSZERO_EVENTHANDLER_HPP
