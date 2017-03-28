//---------------------------------------------------------------------------------------
// Server for CrossZero
// Created by GbaLog
// Link on github.com: https://github.com/GbaLog
//---------------------------------------------------------------------------------------
// TODO:
// - add listener
// - add messages handler
// - add errors handler
//---------------------------------------------------------------------------------------
#ifndef SERVER_HPP
#define SERVER_HPP
//---------------------------------------------------------------------------------------
#include <SFML/Network.hpp>
#include <memory>
#include <deque>
#include <cstdint>
//---------------------------------------------------------------------------------------
#include "detail/server_protocol.hpp"
#include "detail/server_interfaces.hpp"
#include "detail/message_decoder.hpp"
#include "common_data.hpp"
//---------------------------------------------------------------------------------------
namespace server
{
namespace detail
{
//---------------------------------------------------------------------------------------
template<typename Socket>
class ServerBase : IServerBase
{
  using SocketPtr = std::unique_ptr<Socket>;

public:
  ServerBase();

  void pushMessage(const internal::ContainerByte & data);

  void pushClient(SocketPtr newClient);

  template<typename ... Args>
  void emplaceClient(Args && ... args);

private:
  virtual void onMessage(const protocol::Message & msg) override;

  virtual void onDecodeError(const protocol::Error & code) override;

  MessageDecoder decoder_;
  std::vector<SocketPtr> sockets_;
};
//---------------------------------------------------------------------------------------
} //detail
//---------------------------------------------------------------------------------------
using TcpServer = detail::ServerBase<sf::TcpSocket>;
using UdpServer = detail::ServerBase<sf::UdpSocket>;
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
// IMPLEMENTATION
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
template<typename Socket>
detail::ServerBase<Socket>::ServerBase()
  :
  decoder_(*this)
{}
//---------------------------------------------------------------------------------------
template<typename Socket>
void detail::ServerBase<Socket>::pushMessage(const internal::ContainerByte & data)
{
  decoder_.addDataAndTryToDecode(data);
}
//---------------------------------------------------------------------------------------
template<typename Socket>
void detail::ServerBase<Socket>::pushClient(SocketPtr newClient)
{
  sockets_.push_back(std::move(newClient));
}
//---------------------------------------------------------------------------------------
template<typename Socket>
template<typename ... Args>
void detail::ServerBase<Socket>::emplaceClient(Args && ... args)
{
  sockets_.emplace_back(std::make_unique<Socket>(std::forward<Args>(args)...));
}
//---------------------------------------------------------------------------------------
template<typename Socket>
void detail::ServerBase<Socket>::onMessage(const protocol::Message & msg)
{}
//---------------------------------------------------------------------------------------
template<typename Socket>
void detail::ServerBase<Socket>::onDecodeError(const protocol::Error & code)
{}
//---------------------------------------------------------------------------------------
} //server
//---------------------------------------------------------------------------------------
#endif //SERVER_HPP
//---------------------------------------------------------------------------------------
