#include "main_menu.hpp"
#include "mouse_event.hpp"

extern MouseEventSubject mouseSubject;

MainMenu::MainMenu(int _count)
{
    sampleBtn.setSize( sf::Vector2f(200.f, 50.f) );
    interval = 10;

    buttons.resize(_count);
    int i = 0;
    // TODO: Чем заменить итератор
    for ( auto& num : buttons ) {
        num = sampleBtn;
        num.setString( std::to_wstring(i) );
        num.setPosition( sf::Vector2f( 10.f, 40.f*i ) );
        ++i;
        
        mouseSubject.subscribe(dynamic_cast<MouseEventObserver *> (&num));
    }
}

void MainMenu::update(sf::RenderWindow& app)
{
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
}

UI::Controls::Button& MainMenu::operator[](const unsigned int& i)
{
    return buttons.at(i);
}

void MainMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform = getTransform();
    for ( auto& num : buttons ) {
        target.draw(num, states);
    }
}
