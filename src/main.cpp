#include <SFML/Graphics.hpp>
#include "screen.hpp"
#include "settings_screen.hpp"
#include "shared_font.hpp"
#include "server/server.hpp"

int main(int argc, char * argv[]) {
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


	std::vector<UI::Screen::Base*> screens;
	int screen = 0;

	UI::Screen::Background background;
    UI::Screen::TitleScreen titleScreen;
	UI::Screen::FPSCounter fps_counter;
	UI::Screen::Settings settings_menu;
	screens = {
        &background,
        &titleScreen,
        &settings_menu,
        &fps_counter
	};

    while (screen >= 0) {
        sf::Event event;
        while (app.pollEvent(event)) {
            if (sf::Event::Closed == event.type)
                app.close();

            if (sf::Event::Resized == event.type)
                app.setView(view = sf::View(sf::FloatRect(0.f, 0.f, static_cast<float>(app.getSize().x), static_cast<float>(app.getSize().y))));
        }

        screen = screens[screen]->Run(app);
        screens[1]->Run(app);
        screens[2]->Run(app);
        screens[3]->Run(app);
        app.display();
    }

    return EXIT_SUCCESS;
}
