#include "main_menu.hpp"
#include "mouse_event.hpp"
#include "screen.hpp"
#include "settings_screen.hpp"
#include <SFML/Network.hpp>
#include <thread>

// extern MouseEventSubject mouseSubject;

extern UI::Screen::Base *topScreen;
extern UI::Screen::GameScreen *gameScreen;
extern UI::Screen::LeaderBoard *leaderboardScreen;
extern UI::Screen::Settings *settingsScreen;
extern UI::Screen::ScreenManager *screenmgr;
extern UI::Screen::LoadingScreen *loadingScreen;
extern UI::Screen::ConnectionError *errorScreen;

extern sf::RenderWindow *app;

void FindMatch()
{
    screenmgr->ChangeTo(loadingScreen, SCREEN_LAYER_TOP);
    loadingScreen->setString("Connecting to the server...");

    std::thread connThread([](){
        sf::TcpSocket client;
        sf::Socket::Status status = client.connect("127.0.0.1", 8989);

        if (status == sf::Socket::Done)
        {
            std::cout << "Connected to 127.0.0.1" << std::endl;
            screenmgr->ChangeTo(gameScreen, SCREEN_LAYER_TOP);

            size_t received;
            uint8_t status;
            if (client.receive(&status, sizeof(uint8_t), received) != sf::Socket::Done)
            {
                errorScreen->setString("Cannot receive packet.");
                screenmgr->ChangeTo(errorScreen, SCREEN_LAYER_TOP);
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

    void onMouseUp()
    {
        UI::Controls::Button::onMouseUp();
        // screenmgr->ChangeTo(gameScreen, SCREEN_LAYER_TOP);
        FindMatch();
    }
};

class LeaderboardButton : public UI::Controls::Button {
public:
    LeaderboardButton() {}

    friend UI::Controls::Button;

    void onMouseUp()
    {
        UI::Controls::Button::onMouseUp();
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
