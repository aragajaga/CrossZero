//---------------------------------------------------------------------------------------
#ifndef SERVER_INTERFACES_HPP
#define SERVER_INTERFACES_HPP
//---------------------------------------------------------------------------------------
#include <SFML/Network.hpp>
//---------------------------------------------------------------------------------------
#include "server_protocol.hpp"
//---------------------------------------------------------------------------------------
namespace server
{
namespace detail
{
//---------------------------------------------------------------------------------------
struct IServerBase
{
  virtual ~IServerBase() {}

  virtual void onMessage(const protocol::Message & msg) = 0;
  virtual void onDecodeError(const protocol::Error & code) = 0;
};
//---------------------------------------------------------------------------------------
struct IServerConnectionMng
{
  virtual ~IServerConnectionMng() {}

  virtual void onNewConnect(const sf::TcpSocket & newConnection) = 0;
};
//---------------------------------------------------------------------------------------
} //detail
} //server
//---------------------------------------------------------------------------------------
#endif // SERVER_INTERFACES_HPP
