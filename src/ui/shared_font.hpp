#pragma once

#include <SFML/Graphics.hpp>

class SharedFont {
private:
    SharedFont() {}
    SharedFont(const SharedFont&);
    SharedFont& operator=(SharedFont&);
public:
    static SharedFont& getInstance()
    {
        static SharedFont instance;
        return instance;
    }

    sf::Font font;
};
