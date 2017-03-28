//---------------------------------------------------------------------------------------
// Server for CrossZero
// Created by GbaLog
// Link on github.com: https://github.com/GbaLog
//---------------------------------------------------------------------------------------
#ifndef SERVER_HPP
#define SERVER_HPP
//---------------------------------------------------------------------------------------
#include <SFML/Network.hpp>
#include <utility>
#include <string>
#include <memory>
#include <vector>
#include <cstdint>
//---------------------------------------------------------------------------------------
namespace server
{
namespace detail
{
namespace internal
{
//---------------------------------------------------------------------------------------
constexpr const uint8_t endOfMessage = 0x03;
//---------------------------------------------------------------------------------------
enum class Command : uint8_t
{
  JustMessage   = 0x01,
  ServerMessage = 0x02,
  TestMessage   = 0x03,
  Command       = 0x04,
};
//---------------------------------------------------------------------------------------
enum class DirectionMessage : uint8_t
{
  ToServer          = 0x01,
  ToAllClient       = 0x02,
  ToConcreteClient  = 0x03,
};
//---------------------------------------------------------------------------------------
using VecByte = std::vector<uint8_t>;
//---------------------------------------------------------------------------------------
struct MessageHeader
{
  Command command_;
  DirectionMessage dir_;
  uint8_t toClient_;
};
//---------------------------------------------------------------------------------------
struct MessageBody
{
  VecByte data_;
};
//---------------------------------------------------------------------------------------
struct Message
{
  MessageHeader header_;
  MessageBody   body_;
};
//---------------------------------------------------------------------------------------
} //internal
//---------------------------------------------------------------------------------------
template<typename Socket>
class ServerBase
{
public:
  void pushMessage(const internal::VecByte & data);

private:
  using SocketPtr = std::unique_ptr<Socket>;

  class DecodeBuffer;

  std::vector<SocketPtr> sockets_;
};
//---------------------------------------------------------------------------------------
template<typename Socket>
class ServerBase<Socket>::DecodeBuffer
{
public:
  void addDataAndTryToDecode(const internal::VecByte & data);

private:
  internal::VecByte buffer_;
};
//---------------------------------------------------------------------------------------
} //detail
//---------------------------------------------------------------------------------------
using TcpServer = detail::ServerBase<sf::TcpSocket>;
using UdpServer = detail::ServerBase<sf::UdpSocket>;
//---------------------------------------------------------------------------------------
} //server
//---------------------------------------------------------------------------------------
#endif //SERVER_HPP
//---------------------------------------------------------------------------------------
