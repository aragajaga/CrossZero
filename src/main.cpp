#include <SFML/Graphics.hpp>
#include "screen.hpp"
#include "settings_screen.hpp"
#include "shared_font.hpp"
#include "server/server.hpp"
#include "mouse_event.hpp"

MouseEventSubject mouseSubject;
sf::Clock animationClock;

std::vector<Animation *> animations;

int main(int argc, char * argv[]) {
    #ifdef DEBUG
    std::cout << "This is a debug build" << std::endl;
    #endif
    
    /* server::ServerConnectionMng mng;
    mng.listen();

    sf::TcpSocket sock;
    sock.connect("192.168.10.38", 1337);

    */
    // Загрузка ресов
    SharedFont::getInstance().font.loadFromFile("res/CZ.otf");

    sf::ContextSettings settings;
    //settings.antialiasingLevel = 8;

    sf::RenderWindow app(sf::VideoMode(640, 360), "CrossZero", sf::Style::Default, settings);

    sf::View view(app.getDefaultView());
    app.setFramerateLimit(60);
    app.setVerticalSyncEnabled(false);


    animations = std::vector<Animation *> ();

	std::vector<UI::Screen::Base*> screens;
	int screen = 0;

	mouseSubject = MouseEventSubject();
    animationClock = sf::Clock();
    
    UI::Screen::Background background;
    UI::Screen::TitleScreen titleScreen;
	// UI::Screen::FPSCounter fps_counter;
	// UI::Screen::Settings settings_menu;

    while (app.isOpen()) {
        sf::Event event;
        while (app.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                app.close();

            if (event.type == sf::Event::Resized)
                app.setView(view = sf::View(sf::FloatRect(0.f, 0.f, static_cast<float>(app.getSize().x), static_cast<float>(app.getSize().y))));
            
            if (event.type == sf::Event::MouseMoved)
                mouseSubject.mouseMove(event);
            
            if (event.type == sf::Event::MouseButtonPressed)
                mouseSubject.click(event);
            
            if (event.type == sf::Event::MouseButtonReleased)
                mouseSubject.clickRelease(event);
        }

        background.Run(app);
        titleScreen.Run(app);
        
        app.display();
    }

    return EXIT_SUCCESS;
}
