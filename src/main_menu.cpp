#include "main_menu.hpp"
#include "mouse_event.hpp"
#include "screen.hpp"
#include "settings_screen.hpp"

// extern MouseEventSubject mouseSubject;

extern UI::Screen::Base *topScreen;
extern UI::Screen::GameScreen *gameScreen;
extern UI::Screen::Settings *settingsScreen;
extern UI::Screen::ScreenManager *screenmgr;

extern sf::RenderWindow *app;

class PlayButton : public UI::Controls::Button {
public:
    PlayButton()
    {
        
    }
    
    friend UI::Controls::Button;
    
    void onMouseUp()
    {
        UI::Controls::Button::onMouseUp();
        screenmgr->ChangeTo(gameScreen, SCREEN_LAYER_TOP);
    }
};

class SettingsButton : public UI::Controls::Button {
public:
    SettingsButton()
    {
        
    }
    
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
    
    leaderboardButton = new UI::Controls::Button();
    leaderboardButton->setInitialPos(sf::Vector2f(dim.x/2.f, dim.y/2.f));
    leaderboardButton->setOrigin(sf::Vector2f(100.f, 25.f));
    leaderboardButton->setString("Leaderboard");
    screen->m_mouseEvtSub.subscribe(leaderboardButton);
    
    settingsButton = new SettingsButton();
    settingsButton->setInitialSize(sf::Vector2f(200.f, 50.f));
    settingsButton->setInitialPos(sf::Vector2f(dim.x/2.f, dim.y/3.f * 2));
    settingsButton->setOrigin(sf::Vector2f(100.f, 25.f));
    settingsButton->setString("Settings");
    screen->m_mouseEvtSub.subscribe(settingsButton);
    
    #ifdef DEBUG
    std::cout << "[MainMenu] Constructed" << std::endl;
    #endif
}

void MainMenu::update(sf::RenderWindow& app)
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
