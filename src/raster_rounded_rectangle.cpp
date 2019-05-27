#include <cmath>
#include <SFML/Graphics.hpp>

namespace UI {

namespace Draw {

class RasterRoundedRectangle : public sf::Drawable, public sf::Transformable {
public:
    RasterRoundedRectangle()
    {
        base.setPointCount(12);
    }

    void update(
        int     xi,xy;
        float   xj, xy;
        int     fortyFiveDegree;
        float   radSq;
        float   fractional;
        float   roundedDown;

        std::vector<uint8_t> pxlBuf(roundness*16);

        float width = std::ceil(roundness)*2+3; // Ќам нужно немного места дл€ маневра в результирующем массиве, таким образом, +3
        float height = width;
        pxlBuf.resize(width*width);


        base.setPoint(0,  sf::Vector2f(0,                   roundness       ));
        base.setPoint(1,  sf::Vector2f(roundness,           roundness       ));
        base.setPoint(2,  sf::Vector2f(roundness,           0               ));
        base.setPoint(3,  sf::Vector2f(size.x-roundness,    0               ));
        base.setPoint(4,  sf::Vector2f(size.x-roundness,    roundness       ));
        base.setPoint(5,  sf::Vector2f(size.x,              roundness       ));
        base.setPoint(6,  sf::Vector2f(size.x,              size.y-roundness));
        base.setPoint(7,  sf::Vector2f(size.x-roundness,    size.y-roundness));
        base.setPoint(8,  sf::Vector2f(size.x-roundness,    size.y          ));
        base.setPoint(9,  sf::Vector2f(roundness,           size.y          ));
        base.setPoint(10, sf::Vector2f(roundness,           size.y-roundness));
        base.setPoint(11, sf::Vector2f(0,                   size.y-roundness));
    );

    void draw(sf::RenderTarget& target, sf::RenderStates states)
    {

    }

private:
    sf::Image circle;
    sf::ConvexShape base;
    sf::Vector2f size;
    float roundness;
};

}

}
