#include <SFML/Graphics.hpp>
#include "screen.hpp"
#include "settings_screen.hpp"
#include "shared_font.hpp"
#include "server/server.hpp"
#include "mouse_event.hpp"
#include <cstring>

// MouseEventSubject mouseSubject;
sf::Clock animationClock;

sf::RenderWindow *app;
UI::Screen::ScreenManager *screenmgr;
UI::Screen::Base *topScreen;
UI::Screen::GameScreen *gameScreen;
UI::Screen::LeaderBoard *leaderboardScreen;
UI::Screen::Settings *settingsScreen;
std::vector<Animation *> animations;

sf::Font *font_system;

sf::Texture *mark_texture;

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
    font_system = new sf::Font();
    font_system->loadFromFile("res/cour.ttf");
    
    sf::Image mark_image;
    mark_image.loadFromFile("res/mark.bmp");
    mark_image.createMaskFromColor(sf::Color::Magenta);
    
    mark_texture = new sf::Texture();
    mark_texture->loadFromImage(mark_image);
    mark_texture->setSmooth(true);

    sf::ContextSettings settings;
    //settings.antialiasingLevel = 8;

    app = new sf::RenderWindow(sf::VideoMode(640, 360), "CrossZero", sf::Style::Default, settings);

    sf::View view(app->getDefaultView());
    app->setFramerateLimit(60);
    app->setVerticalSyncEnabled(false);

    animations = std::vector<Animation *> ();
    // mouseSubject = MouseEventSubject();
    animationClock = sf::Clock();
    
    UI::Screen::Background background;
    UI::Screen::TitleScreen titleScreen;
    UI::Screen::LoadingScreen loadingScreen;
    UI::Screen::FPSCounter fps_counter;
    
    gameScreen = new UI::Screen::GameScreen();
    settingsScreen = new UI::Screen::Settings();
    leaderboardScreen = new UI::Screen::LeaderBoard();
    
    // UI::Screen::Settings settings_menu;

    // topScreen = &loadingScreen;
    
    screenmgr = new UI::Screen::ScreenManager();
    screenmgr->ChangeTo(&background, SCREEN_LAYER_BACKGROUND);
    screenmgr->ChangeTo(&loadingScreen, SCREEN_LAYER_TOP);
    screenmgr->ChangeTo(&fps_counter, SCREEN_LAYER_OVERLAY);

    while (app->isOpen()) {
        sf::Event event;
        while (app->pollEvent(event)) {
            screenmgr->postEvent(event);
            
            if (event.type == sf::Event::KeyPressed)
                if (event.key.code == sf::Keyboard::Escape)
                    screenmgr->ChangeTo(&titleScreen, SCREEN_LAYER_TOP);
            
            if (event.type == sf::Event::Closed)
                app->close();

            if (event.type == sf::Event::Resized)
                app->setView(view = sf::View(sf::FloatRect(0.f, 0.f, static_cast<float>(app->getSize().x), static_cast<float>(app->getSize().y))));
        }

        screenmgr->Tick(*app);
        
        app->display();
    }

    return EXIT_SUCCESS;
}
