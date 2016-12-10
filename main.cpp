#include <cmath>
#include <random>
#include <clocale>
#include "ui/colorscheme.hpp"
#include "ui/button.hpp"
#include "RoundedRectangleShape.hpp"
#include "ScreenManager.hpp"
#include "simple_particles.hpp"
#include "mainmenu.hpp"

sf::Font arial;
Screen screen;

int main(int argc, char* argv[])
{
    /*//////////////////////////////
    // INITIALIZATION             //
    //////////////////////////////*/
    arial.loadFromFile( "res/arial.ttf" );



    sf::RenderWindow app(sf::VideoMode(640, 480), "CrossZero");
    screen.setWnd(&app);

    sf::View view( app.getDefaultView() );
    app.setFramerateLimit(60);
    app.setVerticalSyncEnabled(false);



    // Партикли на фоне
    const int elems = 20;
    const int speed = 3;

    auto parts = SimpleParticlesBuilder::create()
        .add("res/xo.png", sf::IntRect(0, 0, 24, 24), 10)
        .add("res/xo.png", sf::IntRect(24, 0, 24, 24), 10)
        .setWindowParams(800, 600)
        .setSpeed(3)
        .build();



    sf::Text header;
        header.setFont(arial);
        header.setCharacterSize( app.getSize().y * 72/480 );
        header.setString("CrossZero");
        header.setFillColor( sf::Color(224, 224, 221) );



    MainMenu mainMenu(3);
    mainMenu[0].setString("Play");
    mainMenu[1].setString("Leaderboard");
    mainMenu[2].setString("Settings");




    while (app.isOpen())
    {
        /*//////////////////////////////
        // GAME LOOP TASKS            //
        //////////////////////////////*/

        parts.update();
        mainMenu.update();
        header.setCharacterSize( app.getSize().y * 72/480 );
        header.setPosition( (app.getSize().x - header.getLocalBounds().width )/2, app.getSize().y * 72/480 );



        /*//////////////////////////////
        // EVENT HANDLING             //
        //////////////////////////////*/
        sf::Event event;
        while ( app.pollEvent(event) )
        {
            if ( sf::Event::Closed == event.type )
                app.close();

            if ( sf::Event::Resized == event.type )
                app.setView( view = sf::View( sf::FloatRect( 0.f, 0.f, static_cast<float>( app.getSize().x ), static_cast<float>( app.getSize().y ) ) ) );
        }



        /*//////////////////////////////
        // DRAWING                    //
        //////////////////////////////*/
        app.clear( Color::cocoaDark );

        for( const auto& it : parts.getSprites() )
           app.draw(it);

        app.draw(header);
        app.draw(mainMenu);

        app.display();
    }



    return EXIT_SUCCESS;
}
