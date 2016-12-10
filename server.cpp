/////////////////////////////////////////////////////////////////////////////////////////
#include "server.hpp"
#include <iostream>
#include <thread>
#include <chrono>
/////////////////////////////////////////////////////////////////////////////////////////
Server::Server( const unsigned short port )
    :
    maxGames{2},
    port{port}
{
    listener.listen(port);
}
/////////////////////////////////////////////////////////////////////////////////////////
void Server::run()
{
    std::pair<sf::TcpSocket*, sf::TcpSocket*> twoClients{ nullptr, nullptr };
    while( games.size() <= maxGames )
    {
        sf::TcpSocket* client = new sf::TcpSocket;
        if( listener.accept(*client) == sf::Socket::Done )
        {
            std::cout 
                << "Client connected: "
                << client->getRemoteAddress()
                << "\n";
            if( games.size() <= maxGames )
            {
                if( twoClients.first == nullptr )
                {
                    twoClients.first = client;
                    char data[2]{'x'};
                    client->send(data, 1);
                }
                else if( twoClients.second == nullptr )
                {
                    twoClients.second = client;
                    char data[2]{'o'};
                    client->send(data, 1);
                    std::cout
                        << "Game is running now\n";
                    games.push_back(Game{});
                    games.back().setClients(twoClients.first, twoClients.second);
                    games.back().run();
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
    selector.add(*firstPlayer);
    selector.add(*secondPlayer);
    
    firstPlayerWalking = true;
    
    while( !endOfGame )
    {
        if( selector.wait() )
        {
            if( selector.isReady(*firstPlayer) )
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
            else if( selector.isReady(*secondPlayer) )
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
/////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    Server serv{1337};
    serv.run();
}