#include <SFML/Graphics.hpp>
#include "screen.hpp"
#include "settings_screen.hpp"
#include "shared_font.hpp"
#include "server/server.hpp"
#include "mouse_event.hpp"
#include <cstring>

MouseEventSubject mouseSubject;
sf::Clock animationClock;

sf::RenderWindow *app;
std::vector<Animation *> animations;

#define CHIP_O false;
#define CHIP_X true;

struct ClientPost {
    uint8_t coord;
};

void host()
{
    std::cout << "Starting server" << std::endl;
    
    sf::TcpListener listener;
    if (listener.listen(8989) != sf::Socket::Done)
        return;

    sf::TcpSocket client;
    if (listener.accept(client) != sf::Socket::Done)
        return;
    std::cout << "Client connected" << std::endl;
    
    bool assignedChip = CHIP_X;
    if (client.send(&assignedChip, sizeof(bool)) != sf::Socket::Done)
        return;
    std::cout << "Assigned chip to client: " << (assignedChip ? 'X' : 'O') << std::endl;
    
    struct ClientPost cli_packet;
    size_t received;
    client.receive(&cli_packet, sizeof(struct ClientPost), received);
    std::cout << "Player did move at cell: " << static_cast<int> (cli_packet.coord) << std::endl;
}

int main(int argc, char * argv[]) {
    
    #ifdef DEBUG
    std::cout << "This is a debug build" << std::endl;
    #endif
    
    bool host_arg = false;
    
    for (size_t argi = 1; argi < argc; argi++)
    {
        if (std::strcmp(argv[argi], "--host") == 0) host_arg = true;
    }
    
    if (host_arg)
    {
        host();
        exit(0);
    }
    
    sf::TcpSocket client;
    sf::Socket::Status status = client.connect("127.0.0.1", 8989);
    std::cout << "Connecting to server..." << std::endl;
    
    if (status == sf::Socket::Done) {        
        std::cout << "Connected!" << std::endl;
        
        bool assignedChip;
        size_t received;
        if (client.receive(&assignedChip, sizeof(bool), received) != sf::Socket::Done)
        {
            exit(1);
        }
        std::cout << "Assigned chip: " << (assignedChip ? 'X' : 'O') << std::endl;
        
        struct ClientPost cli_post;
        cli_post.coord = 4;
        
        if (client.send(&cli_post, sizeof(struct ClientPost)) != sf::Socket::Done)
            exit(1);
    } else {
        std::cout << "Cannot connect to server. Offline mode." << std::endl;
    }
    
    
    
    /* server::ServerConnectionMng mng;
    mng.listen();

    sf::TcpSocket sock;
    sock.connect("192.168.10.38", 1337);

    */
    // Загрузка ресов
    SharedFont::getInstance().font.loadFromFile("res/CZ.otf");

    sf::ContextSettings settings;
    //settings.antialiasingLevel = 8;

    app = new sf::RenderWindow(sf::VideoMode(640, 360), "CrossZero", sf::Style::Default, settings);

    sf::View view(app->getDefaultView());
    app->setFramerateLimit(60);
    app->setVerticalSyncEnabled(false);

    animations = std::vector<Animation *> ();
    mouseSubject = MouseEventSubject();
    animationClock = sf::Clock();
    
    UI::Screen::Background background;
    UI::Screen::TitleScreen titleScreen;
    // UI::Screen::FPSCounter fps_counter;
    // UI::Screen::Settings settings_menu;

    while (app->isOpen()) {
        sf::Event event;
        while (app->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                app->close();

            if (event.type == sf::Event::Resized)
                app->setView(view = sf::View(sf::FloatRect(0.f, 0.f, static_cast<float>(app->getSize().x), static_cast<float>(app->getSize().y))));
            
            if (event.type == sf::Event::MouseMoved)
                mouseSubject.mouseMove(event);
            
            if (event.type == sf::Event::MouseButtonPressed)
                mouseSubject.click(event);
            
            if (event.type == sf::Event::MouseButtonReleased)
                mouseSubject.clickRelease(event);
        }

        background.Run(*app);
        titleScreen.Run(*app);
        
        app->display();
    }

    return EXIT_SUCCESS;
}
