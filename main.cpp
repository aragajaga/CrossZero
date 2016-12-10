#include <iostream>
#include <vector>
#include <thread>
#include <cmath>
#include <random>
#include <clocale>
#include <SFML/Graphics.hpp>
#include "RoundedRectangleShape.hpp"


sf::Font arial;

unsigned int SCREENWIDTH = 640,
             SCREENHEIGHT = 480;

namespace ui {

////////////////////////////////////////////////////////////////////////////////

    class Control : public sf::Drawable, public sf::Transformable {

    };

////////////////////////////////////////////////////////////////////////////////

    class Button : public Control {
    public:
        Button()
        {
            base.setCornersRadius( 2.f );
            base.setCornerPointCount( 4 );
            base.setFillColor( sf::Color( 149, 141, 134 ) );

            text.setFont( arial );
            text.setString( "< Unnamed Item >" );
            text.setFillColor( sf::Color( 224, 224, 221 ) );
        }

        void setString (sf::String str)
        {
            text.setString(str);
            update();
        }

        void setSize(sf::Vector2f size)
        {
            m_size = size;
            update();
        }

        sf::Vector2f getSize() const {
            return m_size;
        }

        void setPosition(sf::Vector2f position)
        {
            m_position = position;
            update();
        }

    private:
        void update()
        {
            base.setSize( m_size );
            base.setPosition( m_position.x, m_position.y );
            sf::FloatRect textBounds = text.getLocalBounds();
            float textCharacterSize = m_size.y*0.48f;
            text.setCharacterSize( textCharacterSize );
            text.setPosition(m_position.x + m_size.x/2.f - textBounds.width/2.f, m_position.y + m_size.y/2.f - textCharacterSize/2.f);
        }

        void draw(sf::RenderTarget &target, sf::RenderStates states) const
        {
            target.draw( base, states );
            target.draw( text, states );
        }

        std::wstring label;
        sf::Vector2f m_size;
        sf::Vector2f m_position;
        sf::RoundedRectangleShape base;
        sf::Text text;
    };

////////////////////////////////////////////////////////////////////////////////
}

class ScreenManager
{
public:
    ScreenManager( sf::RenderWindow &_wnd ) : wnd(_wnd) {};

    float calcRelativeByX( const float &value ) const { return wnd.getSize().x * value; };
    float calcRelativeByY( const float &value ) const { return wnd.getSize().y * value; };

    float getPxMenuVMargin() { return menuVMargin * wnd.getSize().y; }

private:
    float menuVMargin = .15f;
    sf::RenderWindow& wnd;
};

class MainMenuButtons : public sf::Drawable, public sf::Transformable {
public:
    MainMenuButtons( int _count )
    {
        sampleBtn.setSize( sf::Vector2f(200.f, 50.f) );

        int i = 0;
        buttons.resize( _count );
        for ( auto &num : buttons ) {
            num = sampleBtn;
            num.setString( std::to_wstring(i) );
            num.setPosition( sf::Vector2f( 10.f, 40.f*i ) );
            i++;
        }
    }

    void update()
    {
        int i = 0;
        for ( auto &num : buttons ) {
            num.setPosition( sf::Vector2f( (SCREENWIDTH - SCREENHEIGHT * (sampleBtn.getSize().y/480.f)*4 )/2,
                                           ( SCREENHEIGHT - SCREENHEIGHT * sampleBtn.getSize().y/480.f*buttons.size() )/2 + SCREENHEIGHT*(sampleBtn.getSize().y+10)/480.f*i ));
            num.setSize( sf::Vector2f( SCREENHEIGHT * (sampleBtn.getSize().y / 480.f)*4, SCREENHEIGHT * (sampleBtn.getSize().y / 480.f) ) );
            i++;
        }
    }

    ui::Button &operator[](const unsigned int &i)
    {
        return buttons.at(i);
    }

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        for ( auto &num : buttons ) {
            target.draw( num, states );
        }
    }

    ui::Button sampleBtn;

    std::vector<ui::Button> buttons;
};

bool verbose = false;

int console()
{
    std::wstring m;
    std::wcout << L"Консоль отладки. Введите /help чтобы получить список доступных комманд.\n";
    while (true) {
        std::cout << "> ";
        std::wcin >> m;

        if ( !m.find(L"/help") ) {
            std::wcout << L"/help\tCправка.\n";
            std::wcout << L"/fps\tУправление фреймрейтом.\n";
            std::wcout << L"/menu\tУправление элементами главного меню.\n";
            std::wcout << L"/terminate\tНемедленное завершение приложения.\n";
            std::wcout << L"/verbose\tВыводить все события.\n";
        }

        if ( !m.find(L"/fps") ) {
        /// TODO: Получить доступ к объекту другого потока.
        }

        if ( !m.find(L"/menu") ) {
            std::wcout << "/updatemenuentry [i] <label>\n";
        }

        if ( !m.find(L"/terminate") ) {
            exit(0);
        }

        if ( !m.find(L"/verbose") ) {
            verbose = verbose?false:true;
            std::wcout << "State: " << verbose;
        }

        std::cout << std::endl;
    }
    return 0;
}

int graphics()
{
    /*//////////////////////////////
    // INITIALIZATION             //
    //////////////////////////////*/
    arial.loadFromFile( "arial.ttf" );



    sf::RenderWindow app(sf::VideoMode(SCREENWIDTH, SCREENHEIGHT), "CrossZero");
    ScreenManager screenManager(app);
    sf::View view( app.getDefaultView() );
    app.setFramerateLimit(60);
    app.setVerticalSyncEnabled(false);



    // Партикли на фоне
    const int elems = 20;
    const int speed = 3;

    sf::Rect<int> rect( 0, 0, 24, 24 );

    SimpleParticles parts{"x.png", rect, elems};
    parts.setWindowParams(SCREENWIDTH, SCREENHEIGHT);
    parts.setSpeed(speed);

    parts.add("o.png", rect, 2);



    sf::Text header;
        header.setFont(arial);
        header.setCharacterSize( app.getSize().y * 72/480 );
        header.setString("CrossZero");
        header.setFillColor( sf::Color(224, 224, 221) );



    MainMenuButtons mainMenuButtons(3);
    mainMenuButtons[0].setString("Play");
    mainMenuButtons[1].setString("Leaderboard");
    mainMenuButtons[2].setString("Settings");




    while (app.isOpen())
    {
        /*//////////////////////////////
        // GAME LOOP TASKS            //
        //////////////////////////////*/
        SCREENWIDTH = app.getSize().x;
        SCREENHEIGHT = app.getSize().y;

        parts.update();
        mainMenuButtons.update();
        header.setCharacterSize( SCREENHEIGHT * 72/480 );
        header.setPosition( (SCREENWIDTH - header.getLocalBounds().width )/2, SCREENHEIGHT * 72/480 );



        /*//////////////////////////////
        // EVENT HANDLING             //
        //////////////////////////////*/
        sf::Event event;
        while ( app.pollEvent(event) )
        {
            if ( event.type == sf::Event::Closed ) {
                if ( verbose ) std::cout << "\n[EVENT] Render window closed.";
                app.close();
            }

            if ( event.type == sf::Event::Resized ) {
                app.setView( view = sf::View( sf::FloatRect( 0.f, 0.f, static_cast<float>( app.getSize().x ), static_cast<float>( app.getSize().y ) ) ) );
            }
        }



        /*//////////////////////////////
        // DRAWING                    //
        //////////////////////////////*/
        app.clear( sf::Color(94, 88, 80) );

        for( const auto& it : parts.getSprites() )
           app.draw(it);

        app.draw(header);
        app.draw(mainMenuButtons);

        app.display();
    }



    return EXIT_SUCCESS;
}



int main()
{
    setlocale(LC_ALL, "Russian");
    std::thread consoleThread(console);
    std::thread graphicsThread(graphics);


    if ( consoleThread.joinable() ) consoleThread.join();
    if ( graphicsThread.joinable() ) graphicsThread.join();
    return 0;
}
