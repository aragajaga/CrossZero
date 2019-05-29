//---------------------------------------------------------------------------------------
#ifndef SERVER_CONNECTION_MNG_HPP
#define SERVER_CONNECTION_MNG_HPP
//---------------------------------------------------------------------------------------
#include <thread>
#include <iostream>
//---------------------------------------------------------------------------------------
#include "detail/server_interfaces.hpp"
#include "detail/socket_container.hpp"
#include "server_listener.hpp"
//---------------------------------------------------------------------------------------
namespace server
{
//---------------------------------------------------------------------------------------
class ServerConnectionMng : public detail::IServerConnectionMng
{
public:
  ServerConnectionMng();
  ServerConnectionMng(uint16_t port);
  ~ServerConnectionMng();

  ServerConnectionMng(const ServerConnectionMng &) = delete;
  ServerConnectionMng(ServerConnectionMng &&) = delete;
  ServerConnectionMng & operator =(const ServerConnectionMng &) = delete;
  ServerConnectionMng & operator =(ServerConnectionMng &&) = delete;

  void setPort(uint16_t port);

  void listen();

  //IServerConnectionMng interface
  virtual void onNewConnect(std::shared_ptr<sf::TcpSocket> && newConnection) override;

private:
  uint16_t port_;
  ServerListener listener_;
  TcpSocketContainer container_;
  std::thread thread_;
};
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
// IMPLEMENTATION
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
ServerConnectionMng::ServerConnectionMng()
  :
  port_(1337),
  listener_(*this)
{}
//---------------------------------------------------------------------------------------
ServerConnectionMng::ServerConnectionMng(uint16_t port)
  :
  port_(port),
  listener_(*this)
{}
//---------------------------------------------------------------------------------------
ServerConnectionMng::~ServerConnectionMng()
{
  listener_.setListen(false);
  thread_.join();
}
//---------------------------------------------------------------------------------------
void ServerConnectionMng::setPort(uint16_t port)
{
  port_ = port;
}
//---------------------------------------------------------------------------------------
void ServerConnectionMng::listen()
{
  if (!thread_.joinable())
    thread_ = std::thread([&] { listener_.listenPort(port_); });
}
//---------------------------------------------------------------------------------------
void ServerConnectionMng::onNewConnect(std::shared_ptr<sf::TcpSocket> && newConnection)
{
  container_.pushClient(std::move(newConnection));
}
//---------------------------------------------------------------------------------------
} //server
//---------------------------------------------------------------------------------------
#endif // SERVER_CONNECTION_MNG_HPP
//---------------------------------------------------------------------------------------
