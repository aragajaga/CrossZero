#ifndef BRANDING_SCREEN_HPP
#define BRANDING_SCREEN_HPP

#include "screen.hpp"

namespace UI::Screen {

class BrandingScreen : public UI::Screen::Base {
public:
  BrandingScreen();

  int Run(sf::RenderWindow& app) override;
};

}

#endif  // BRANDING_SCREEN_HPP