#include "main_menu.hpp"
#include "mouse_event.hpp"

extern MouseEventSubject mouseSubject;

MainMenu::MainMenu()
{    
    UI::Controls::Button *playButton = new UI::Controls::Button();
    playButton->setSize(sf::Vector2f(200.f, 50.f));
    playButton->setPosition(10.f, 10.f);
    playButton->setString("Play");
    mouseSubject.subscribe(playButton);
    buttons.push_back(playButton);
    
    UI::Controls::Button *leaderboardButton = new UI::Controls::Button();
    leaderboardButton->setSize(sf::Vector2f(200.f, 50.f));
    leaderboardButton->setPosition(10.f, 70.f);
    leaderboardButton->setString("Leaderboard");
    mouseSubject.subscribe(leaderboardButton);
    buttons.push_back(leaderboardButton);
    
    UI::Controls::Button *settingsButton = new UI::Controls::Button();
    settingsButton->setSize(sf::Vector2f(200.f, 50.f));
    settingsButton->setPosition(sf::Vector2f(10.f, 130.f));
    settingsButton->setString("Settings");
    mouseSubject.subscribe(settingsButton);
    buttons.push_back(settingsButton);
    
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
}

void MainMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform = getTransform();
    for ( auto& num : buttons ) {
        target.draw(*num, states);
    }
}
