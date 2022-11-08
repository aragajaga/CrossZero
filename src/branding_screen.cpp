#include "branding_screen.hpp"
#include <memory>
#include <windows.h>
#include <chrono>

namespace UI::Screen {

BrandingScreen::BrandingScreen() {
}

int BrandingScreen::Run(sf::RenderWindow& app)
{
  static auto started = std::chrono::system_clock::now();

  auto elapsed = std::chrono::system_clock::now() - started;

  try {
    app.clear(sf::Color::White);

    auto brandingTexture = std::make_unique<sf::Texture>();
    constexpr auto texturePath = "res/aragajaga.png";

    try {
      if (!brandingTexture->loadFromFile(texturePath)) {
        throw std::runtime_error(std::format("Failed to load texture \"{}\"", texturePath));
      }
    }
    catch (const std::exception& e) {
      ::MessageBoxA(NULL, e.what(), NULL, MB_OK | MB_ICONERROR);
      throw e;
    }

    auto brandingSprite = std::make_unique<sf::Sprite>(*brandingTexture);
    brandingSprite->setPosition(
      (app.getSize().x - brandingSprite->getTexture()->getSize().x) / 2,
      (app.getSize().y - brandingSprite->getTexture()->getSize().y) / 2
    );

    brandingSprite->setColor(sf::Color(255, 255, 255,
      std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count() % 255));

    app.draw(*brandingSprite);
  }
  catch (...) {
    app.close();
  }

  return 0;
}

}
