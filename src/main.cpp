#include <SFML/Graphics.hpp>
#include "screen.hpp"
#include "settings_screen.hpp"
#include "shared_font.hpp"
#include "server/server.hpp"
#include "mouse_event.hpp"
#include <cstring>
#include "gamerule.hpp"
#include <list>
#include <filesystem>

#include "mini/ini.h"

// MouseEventSubject mouseSubject;
sf::Clock animationClock;

sf::RenderWindow *app;
UI::Screen::ScreenManager *screenmgr;
UI::Screen::Base *topScreen;
UI::Screen::GameScreen *gameScreen;
UI::Screen::LeaderBoard *leaderboardScreen;
UI::Screen::Settings *settingsScreen;
UI::Screen::LoadingScreen *loadingScreen;
UI::Screen::TitleScreen *titleScreen;
UI::Screen::ConnectionError *errorScreen;
std::vector<Animation *> animations;

sf::Font *font_system;

sf::Texture *mark_texture;

struct ClientPost {
    uint8_t coord;
};

void host()
{
    std::cout << "Starting server" << std::endl;

    sf::TcpListener listener;
    if (listener.listen(8989) != sf::Socket::Done)
        return;

    std::list<sf::TcpSocket*> clients;

    sf::SocketSelector selector;
    selector.add(listener);

    while (true)
    {
        if (selector.wait())
        {
            if (selector.isReady(listener))
            {
                sf::TcpSocket* client = new sf::TcpSocket;
                if (listener.accept(*client) == sf::Socket::Done)
                {
                    std::cout << "Player connected" << std::endl;
                    clients.push_back(client);
                    selector.add(*client);
                }
                else
                {
                    delete client;
                }
            }
            else
            {
                for (std::list<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); ++it)
                {
                    sf::TcpSocket& client = **it;
                    if (selector.isReady(client))
                    {
                        sf::Packet packet;
                        if (client.receive(packet) == sf::Socket::Done)
                        {
                        }
                    }
                }
            }
        }
    }
}

void generateDefaultSettingsFile(mINI::INIFile &file)
{
    mINI::INIStructure ini;

    ini["settings"]["screen_w"] = "640";
    ini["settings"]["screen_h"] = "360";

    ini["settings"]["antialiasing_level"]   = "0";
    ini["settings"]["framerate_limit"]      = "60";
    ini["settings"]["vsync"]                = "1";

    ini["settings"]["server_ip"]    = "127.0.0.1";
    ini["settings"]["server_port"]  = "8686";
    file.generate(ini);
}

struct GameSettings {
    unsigned int screen_w;
    unsigned int screen_h;

    uint8_t antialiasing_level;
    unsigned int framerate_limit;
    bool vsync;

    std::string server_ip;
    unsigned int server_port;
} game_settings;

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

    mINI::INIFile settings_ini("settings.ini");

    mINI::INIStructure ini;
    if (std::filesystem::exists("settings.ini"))
    {
        settings_ini.read(ini);

        game_settings.screen_w  = std::stoi(ini["settings"]["screen_w"]);
        game_settings.screen_h  = std::stoi(ini["settings"]["screen_h"]);

        game_settings.antialiasing_level    = std::stoi(ini["settings"]["antialiasing_level"]);
        game_settings.framerate_limit       = std::stoi(ini["settings"]["framerate_limit"]);
        game_settings.vsync                 = static_cast<bool>(std::stoi(ini["settings"]["vsync"]));

        game_settings.server_ip     = ini["settings"]["server_ip"];
        game_settings.server_port   = std::stoi(ini["settings"]["server_port"]);
    }
    else {
        generateDefaultSettingsFile(settings_ini);
    }

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

    if (game_settings.antialiasing_level)
        settings.antialiasingLevel = game_settings.antialiasing_level;

    sf::VideoMode video_mode(game_settings.screen_w, game_settings.screen_h);

    app = new sf::RenderWindow(video_mode, "CrossZero", sf::Style::Default, settings);

    sf::View view(app->getDefaultView());

    if (game_settings.framerate_limit)
        app->setFramerateLimit(game_settings.framerate_limit);

    app->setVerticalSyncEnabled(game_settings.vsync);

    animations = std::vector<Animation *> ();
    // mouseSubject = MouseEventSubject();
    animationClock = sf::Clock();

    UI::Screen::Background background;
    UI::Screen::FPSCounter fps_counter;

    gameScreen = new UI::Screen::GameScreen();
    settingsScreen = new UI::Screen::Settings();
    leaderboardScreen = new UI::Screen::LeaderBoard();
    loadingScreen = new UI::Screen::LoadingScreen();
    titleScreen = new UI::Screen::TitleScreen();
    errorScreen = new UI::Screen::ConnectionError();

    // UI::Screen::Settings settings_menu;

    // topScreen = &loadingScreen;

    screenmgr = new UI::Screen::ScreenManager();
    screenmgr->ChangeTo(&background, SCREEN_LAYER_BACKGROUND);
    screenmgr->ChangeTo(loadingScreen, SCREEN_LAYER_TOP);
    screenmgr->ChangeTo(&fps_counter, SCREEN_LAYER_OVERLAY);

    while (app->isOpen()) {
        sf::Event event;
        while (app->pollEvent(event)) {
            screenmgr->postEvent(event);

            if (event.type == sf::Event::KeyPressed)
                if (event.key.code == sf::Keyboard::Escape)
                    screenmgr->ChangeTo(titleScreen, SCREEN_LAYER_TOP);

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
