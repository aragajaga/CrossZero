#include "main_menu.hpp"
#include "mouse_event.hpp"
#include "screen.hpp"
#include "settings_screen.hpp"
#include <SFML/Network.hpp>
#include <thread>
#include "gamerule.hpp"

// extern MouseEventSubject mouseSubject;

extern UI::Screen::Base *topScreen;
extern UI::Screen::GameScreen *gameScreen;
extern UI::Screen::LeaderBoard *leaderboardScreen;
extern UI::Screen::Settings *settingsScreen;
extern UI::Screen::ScreenManager *screenmgr;
extern UI::Screen::LoadingScreen *loadingScreen;
extern UI::Screen::ConnectionError *errorScreen;

extern GameSettings game_settings;
extern void doOpponentTurn(uint8_t cell);

extern sf::RenderWindow *app;
sf::TcpSocket client;

void FindMatch()
{
    screenmgr->ChangeTo(loadingScreen, SCREEN_LAYER_TOP);

    #ifdef DEBUG
    std::string loadingStatus = "Connecting to " + game_settings.server_ip + ":" + std::to_string(game_settings.server_port) +  "...";
    loadingScreen->setString(loadingStatus);
    #else
    loadingScreen->setString("Connecting to server...");
    #endif

    std::thread connThread([](){
        sf::Socket::Status status = client.connect(game_settings.server_ip, game_settings.server_port);

        if (status == sf::Socket::Done)
        {
            std::cout << "Connected to 127.0.0.1" << std::endl;
            loadingScreen->setString("Connected");

            sf::Packet packet;
            while (true)
            {
                if (client.receive(packet) == sf::Socket::Done)
                {
                    sf::Uint8 packet_id;
                    packet >> packet_id;

                    switch (packet_id)
                    {
                    case PACKET_TURN:
                        {
                        sf::Uint8 cell;
                        packet >> cell;

                        std::cout << "[SERVER] Opponent turn: " << static_cast<int> (cell) << std::endl;

                        doOpponentTurn(cell);
                        }
                        break;
                    case PACKET_OPPONENTWAIT:
                        loadingScreen->setString("Waiting opponent...");
                        break;
                    case PACKET_OPPONENTREADY:
                        screenmgr->ChangeTo(gameScreen, SCREEN_LAYER_TOP);
                        break;
                    }
                }
            }

        } else {
            errorScreen->setString("Cannot connect.");
            screenmgr->ChangeTo(errorScreen, SCREEN_LAYER_TOP);
        }
    });
    connThread.detach();
}

class PlayButton : public UI::Controls::Button {
public:
    PlayButton() {}

    friend UI::Controls::Button;

    void onMouseUp(sf::Event& event)
    {
        UI::Controls::Button::onMouseUp(event);
        // screenmgr->ChangeTo(gameScreen, SCREEN_LAYER_TOP);
        FindMatch();
    }
};

class LeaderboardButton : public UI::Controls::Button {
public:
    LeaderboardButton() {}

    friend UI::Controls::Button;

    void onMouseUp(sf::Event& event)
    {
        UI::Controls::Button::onMouseUp(event);
        screenmgr->ChangeTo(leaderboardScreen, SCREEN_LAYER_TOP);
    }
};

class SettingsButton : public UI::Controls::Button {
public:
    SettingsButton() {}

    friend UI::Controls::Button;

    void onMouseClick()
    {
        UI::Controls::Button::onMouseClick();
        screenmgr->ChangeTo(settingsScreen, SCREEN_LAYER_TOP);
    }
};

MainMenu::MainMenu(UI::Screen::Base* screen)
{
    auto dim = app->getSize();

    playButton = new PlayButton();
    playButton->setInitialSize(sf::Vector2f(200.f, 50.f));
    playButton->setInitialPos(sf::Vector2f(dim.x/2.f, dim.y/3.f));
    playButton->setOrigin(sf::Vector2f(100.f, 25.f));
    playButton->setString("Play");
    screen->m_mouseEvtSub.subscribe(playButton);

    leaderboardButton = new LeaderboardButton();
    leaderboardButton->setInitialSize(sf::Vector2f(200.f, 50.f));
    leaderboardButton->setInitialPos(sf::Vector2f(dim.x/2.f, dim.y/2.f));
    leaderboardButton->setOrigin(sf::Vector2f(100.f, 25.f));
    leaderboardButton->setString("Leaderboard");
    screen->m_mouseEvtSub.subscribe(leaderboardButton);

    settingsButton = new SettingsButton();
    settingsButton->setInitialSize(sf::Vector2f(200.f, 50.f));
    settingsButton->setInitialPos(sf::Vector2f(dim.x/2.f, dim.y/3.f * 2.f));
    settingsButton->setOrigin(sf::Vector2f(100.f, 25.f));
    settingsButton->setString("Settings");
    screen->m_mouseEvtSub.subscribe(settingsButton);

    update();

    #ifdef DEBUG
    std::cout << "[MainMenu] Constructed" << std::endl;
    #endif
}

void MainMenu::update()
{
    playButton->update();
    leaderboardButton->update();
    settingsButton->update();
}

void MainMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform = getTransform();
    target.draw(*playButton, states);
    target.draw(*leaderboardButton, states);
    target.draw(*settingsButton, states);

    /* for ( auto& num : buttons ) {
        target.draw(*num, states);
    } */
}
