/////////////////////////////////////////////////////////////////////////////////////////
#include "server.hpp"
#include <iostream>
#include <thread>
#include <chrono>
/////////////////////////////////////////////////////////////////////////////////////////
Server::Server( const unsigned port )
    :
    currentGame{0},
    port{port}
{
    listener.listen(port);
    selector.add(listener);
}
/////////////////////////////////////////////////////////////////////////////////////////
void Server::run()
{
    std::pair<sf::TcpSocket*, sf::TcpSocket*> twoClients{ nullptr, nullptr };
    while( currentGame <= games.size() )
    {
        sf::TcpSocket* client = new sf::TcpSocket;
        if( listener.accept(*client) == sf::Socket::Done )
        {
            std::cout 
                << "Client connected: "
                << client->getRemoteAddress()
                << "\n";
            if( currentGame <= games.size() )
            {
                if( twoClients.first == nullptr )
                {
                    twoClients.first = client;
                }
                else if( twoClients.second == nullptr )
                {
                    twoClients.second = client;
                    games[currentGame].setClients{ twoClients.first, twoClients.second };
                    games[currentGame].run();
                    ++currentGame;
                }
            }
        }
        else
        {
            delete client;
        }
    }
    std::cout
        << "Server is shooting down\n";
}
/////////////////////////////////////////////////////////////////////////////////////////
void Game::setClients( sf::TcpSocket* firstPlayer, sf::TcpSocket* secondPlayer )
{
    this->firstPlayer = firstPlayer;
    this->secondPlayer = secondPlayer;
}
/////////////////////////////////////////////////////////////////////////////////////////
void Game::run()
{
    selector.add(firstPlayer);
    selector.add(secondPlayer);
    
    firstPlayerWalking = true;
    
    while( !endOfGame )
    {
        if( selector.wait() )
        {
            if( selector.isReady(firstPlayer) )
            {
                size_t received{};
                if( firstPlayer->receive(data, 128, received) == sf::Socket::Done )
                {
                    if( firstPlayerWalking )
                    {
                        if( secondPlayer->send(data, 128, received) == sf::Socket::Done )
                        {
                            std::cout << "Receive and resend some message\n";
                            firstPlayerWalking = false;
                        }
                        else
                        {
                            endOfGame = true;
                        }
                    }
                }
            }
            else if( selector.isReady(secondPlayer) )
            {
                size_t received{};
                if( secondPlayer->receive(data, 128, received) == sf::Socket::Done )
                {
                    if( !firstPlayerWalking )
                    {
                        if( firstPlayer->send(data, 128, received) == sf::Socket::Done )
                        {
                            std::cout << "Receive and resend some message\n";
                            firstPlayerWalking = true;
                        }
                        else
                        {
                            endOfGame = true;
                        }
                    }
                }
            }
        }
    }
}