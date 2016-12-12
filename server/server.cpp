/////////////////////////////////////////////////////////////////////////////////////////
// TODO: разобраться с 45...
// Подсказка: данные доходят до пака, но хз куда деваются.
/////////////////////////////////////////////////////////////////////////////////////////
#include "server.hpp"
#include <iostream>
#include <chrono>
#include <thread>
/////////////////////////////////////////////////////////////////////////////////////////
OneGameServer::OneGameServer( sf::TcpSocket* firstClient, sf::TcpSocket* secondClient )
    :
    clients{std::make_pair(firstClient, secondClient)}
{}
/////////////////////////////////////////////////////////////////////////////////////////
OneGameServer::~OneGameServer()
{
    disconnectAll();
}
/////////////////////////////////////////////////////////////////////////////////////////
void OneGameServer::setClients( sf::TcpSocket* firstClient, sf::TcpSocket* secondClient )
{
    disconnectAll();
    clients = std::make_pair(firstClient, secondClient);
}
/////////////////////////////////////////////////////////////////////////////////////////
void OneGameServer::run()
{
    sf::Packet dataPack;
    sf::SocketSelector selector;
    selector.add(*clients.first);
    selector.add(*clients.second);
    while( isGame )
    {
        if( selector.wait() )
        {
            if( !isConnected(clients.first) || !isConnected(clients.second) )
            {
                isGame = false;
                disconnectAll();
                std::cout << "Game is end. First or Second player disconnected\n";
                continue;
            }
            if( selector.isReady(*clients.first) )
            {
                std::cout << "First client is ready.\n";
                if( clients.first->receive(dataPack) == sf::Socket::Done )
                {
                    if( clients.second->send(dataPack) == sf::Socket::Done )
                    {
                        std::cout << "Receive and resend data successfully\n";
                        dataPack.clear();
                    }
                    else
                    {
                        isGame = false;
                        disconnectAll();
                        std::cout << "Game is end. Second player disconnected\n";
                        continue;
                    }
                }
            }
            if( selector.isReady(*clients.second) )
            {
                std::cout << "Second client is ready.\n";
                if( clients.second->receive(dataPack) == sf::Socket::Done )
                {
                    if( clients.first->send(dataPack) == sf::Socket::Done )
                    {
                        std::cout << "Receive and resend data successfully\n";
                        dataPack.clear();
                    }
                    else
                    {
                        isGame = false;
                        disconnectAll();
                        std::cout << "Game is end. First player disconnected\n";
                        continue;
                    }
                }
            }
        }
    }
}
/////////////////////////////////////////////////////////////////////////////////////////
bool OneGameServer::isConnected( sf::TcpSocket* sock )
{
    std::size_t dummy{};
    bool lock = sock->isBlocking();
    if( lock )
        sock->setBlocking(false);
    bool ret = sock->receive(&dummy, 0, dummy) != sf::Socket::Disconnected;
    if( lock )
        sock->setBlocking(true);
}
/////////////////////////////////////////////////////////////////////////////////////////
void OneGameServer::disconnectAll()
{
    delete clients.first;
    delete clients.second;
    clients.first = nullptr;
    clients.second = nullptr;
}
/////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    sf::TcpSocket* firstPlayer = new sf::TcpSocket;
    sf::TcpSocket* secondPlayer = new sf::TcpSocket;
    sf::TcpListener listener;
    listener.listen(1337);
    if( listener.accept(*firstPlayer) == sf::Socket::Done )
    {
        std::cout << "Client connected: " << firstPlayer->getRemoteAddress() << "\n";
    }
    if( listener.accept(*secondPlayer) == sf::Socket::Done )
    {
        std::cout << "Client connected: " << secondPlayer->getRemoteAddress() << "\n";
    }
    OneGameServer server{firstPlayer, secondPlayer};
    std::cout << "Starting game\n";
    server.run();
    std::cout << "Game is end\n";
    //Server serv{1337};
    //serv.run();
}