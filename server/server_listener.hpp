//---------------------------------------------------------------------------------------
#ifndef SERVER_LISTENER_HPP
#define SERVER_LISTENER_HPP
//---------------------------------------------------------------------------------------
#include <SFML/Network.hpp>
#include <thread>
#include <chrono>
#include <atomic>
//---------------------------------------------------------------------------------------
#include "detail/server_interfaces.hpp"
//---------------------------------------------------------------------------------------
namespace server
{
//---------------------------------------------------------------------------------------
class ServerListener
{
public:
  ServerListener(detail::IServerConnectionMng & connectionMng);

  void listenPort(uint16_t port);

  void setListen(bool listen);

private:
  sf::TcpListener listener_;
  std::atomic<bool> listen_;

  detail::IServerConnectionMng & connectionMng_;
};
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
// IMPLEMENTATION
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
ServerListener::ServerListener(detail::IServerConnectionMng & connectionMng)
  :
  connectionMng_(connectionMng),
  listen_(true)
{}
//---------------------------------------------------------------------------------------
void ServerListener::listenPort(uint16_t port)
{
  listener_.listen(port);

  while (listen_)
  {
    sf::TcpSocket sock;
    if (listener_.accept(sock) == sf::Socket::Done)
    {
      connectionMng_.onNewConnect(sock);
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}
//---------------------------------------------------------------------------------------
void ServerListener::setListen(bool listen)
{
  listen_ = listen;
}
//---------------------------------------------------------------------------------------
}
//---------------------------------------------------------------------------------------
#endif // SERVER_LISTENER_HPP
//---------------------------------------------------------------------------------------
