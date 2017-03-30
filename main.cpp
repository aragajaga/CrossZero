#include <iostream>
#include <cmath>
#include <random>
#include "eventhandler.hpp"
#include "ui/colorscheme.hpp"
#include "ui/button.hpp"
#include "RoundedRectangleShape.hpp"
#include "ScreenManager.hpp"
#include "simple_particles.hpp"
#include "mainmenu.hpp"
#include "effects.hpp"
#include "server/server.hpp"

sf::Font arial;
Screen screen;

int main(int argc, char* argv[])
{
  server::ServerConnectionMng mng;
  mng.listen();

  sf::TcpSocket sock;
  sock.connect("192.168.10.38", 1337);
    /*//////////////////////////////
    // INITIALIZATION             //
    //////////////////////////////*/
    arial.loadFromFile( "res/CZ.otf" );

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow app(sf::VideoMode(640, 480), "CrossZero", sf::Style::Default, settings);
    screen.setWnd(&app);

    sf::View view( app.getDefaultView() );
    app.setFramerateLimit(60);
    app.setVerticalSyncEnabled(false);

    EventHandler eventHandler;



    // Партикли на фоне
    auto parts = SimpleParticlesBuilder::create()
        .add("res/xo.png", sf::IntRect(0, 0, 24, 24), 10)
        .add("res/xo.png", sf::IntRect(24, 0, 24, 24), 10)
        .setWindowParams(screen.getWnd()->getSize().x, screen.getWnd()->getSize().y)
        .setSpeed(0.5f)
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

    ui::Button button1;
    button1.setPosition( 50.f, 50.f );
    button1.setSize( 100.f, 20.f );
    button1.setString( L"Мамаша" );
    button1.update();
    eventHandler.push(button1);




    while (app.isOpen())
    {
        /*//////////////////////////////
        // GAME LOOP TASKS            //
        //////////////////////////////*/

        parts.update(box);
        mainMenu.update();
        header.setCharacterSize( app.getSize().y * 72/480 );
        header.setPosition( (app.getSize().x - header.getLocalBounds().width )/2, app.getSize().y * (72-21)/480 );



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

            if ( sf::Event::MouseButtonPressed == event.type ) {
                eventHandler.poll(event);
            }
        }



        /*//////////////////////////////
        // DRAWING                    //
        //////////////////////////////*/
        app.clear( Color::cocoaDark );

        for( const auto& it : parts.getSprites() )
           app.draw(it);

        app.draw(header);
        app.draw(mainMenu);
        app.draw(button1);

        app.display();
    }



    return EXIT_SUCCESS;
}
