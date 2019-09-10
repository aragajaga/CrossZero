#include "main_menu.hpp"
#include "mouse_event.hpp"
#include "screen.hpp"
#include "settings_screen.hpp"

extern MouseEventSubject mouseSubject;

extern UI::Screen::Base *topScreen;
extern UI::Screen::GameScreen *gameScreen;
extern UI::Screen::Settings *settingsScreen;
extern UI::Screen::ScreenManager *screenmgr;

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




MainMenu::MainMenu()
{    
    playButton = new PlayButton();
    playButton->setInitialSize(sf::Vector2f(200.f, 50.f));
    playButton->setOrigin(100.f, 25.f);
    playButton->setPosition(10.f, 10.f);
    playButton->setString("Play");
    mouseSubject.subscribe(playButton);
    // buttons.push_back(playButton);
    
    leaderboardButton = new UI::Controls::Button();
    leaderboardButton->setInitialSize(sf::Vector2f(200.f, 50.f));
    leaderboardButton->setOrigin(100.f, 25.f);
    leaderboardButton->setPosition(10.f, 70.f);
    leaderboardButton->setString("Leaderboard");
    mouseSubject.subscribe(leaderboardButton);
    // buttons.push_back(leaderboardButton);
    
    settingsButton = new SettingsButton();
    settingsButton->setInitialSize(sf::Vector2f(200.f, 50.f));
    settingsButton->setOrigin(100.f, 25.f);
    settingsButton->setPosition(sf::Vector2f(10.f, 130.f));
    settingsButton->setString("Settings");
    mouseSubject.subscribe(settingsButton);
    // buttons.push_back(settingsButton);
    
    #ifdef DEBUG
    std::cout << "[MainMenu] Constructed" << std::endl;
    #endif
}

void MainMenu::update(sf::RenderWindow& app)
{
    #ifdef DEBUG
    std::cout << "[Button] Update. Pos x:" << getPosition().x << " y:"
        << getPosition().y << std::endl;
    #endif
    /*
    const auto& scr = app.getSize();
    const auto& sample = sampleBtn.getSize();
    auto boxH = scr.y - scr.y*((125+72)/480.f);

    int i = 0;
    for ( auto& num : buttons ) {
        // num.setPosition( scr.x/2, i*20 );
        num.setPosition((scr.x-scr.y*sample.y/480.f*sample.x/sample.y)/2,
                scr.y*125/480.f+((boxH-(scr.y*sample.y/480.f*buttons.size()+
                (scr.y*interval/480.f*(buttons.size()-1))))/2+scr.y*(sample.y+
                interval)/480.f*i));

        num.setSize(scr.y * sample.y/480.f * sample.x/sample.y, scr.y *
                sample.y/480.f);

        num.update();
        ++i;
    }
    */
    
    
    auto screen = app.getSize();
    playButton          ->setPosition(screen.x / 2, screen.y / 3);
    playButton          ->update();
    
    leaderboardButton   ->setPosition(screen.x / 2, screen.y / 2);
    leaderboardButton   ->update();
    
    settingsButton      ->setPosition(screen.x / 2, screen.y / 3 * 2);
    settingsButton      ->update();
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
