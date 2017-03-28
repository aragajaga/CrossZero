//---------------------------------------------------------------------------------------
#ifndef SERVER_PROTOCOL_HPP
#define SERVER_PROTOCOL_HPP
//---------------------------------------------------------------------------------------
#include <cstdint>
#include <vector>
//---------------------------------------------------------------------------------------
namespace server
{
namespace protocol
{
//---------------------------------------------------------------------------------------
constexpr const uint8_t endOfMessage = 0x00;
constexpr const int     minimumToDecodeSize = 3;
//---------------------------------------------------------------------------------------
enum class Command : uint8_t
{
  UserMessage   = 0x01,
  ServerMessage = 0x02,
  TestMessage   = 0x03,
  Command       = 0x04,
};
//---------------------------------------------------------------------------------------
enum class Direction : uint8_t
{
  ToServer          = 0x01,
  ToAllClient       = 0x02,
  ToConcreteClient  = 0x03,
};
//---------------------------------------------------------------------------------------
enum class ErrorCode : uint8_t
{
  FirstByteMismatch       = 0x01,
  DirectionByteMismatch   = 0x02,
  ClientByteMismatch      = 0x03,
  NoEndOfMessage          = 0x04,
  NoDataForDecoding       = 0x05,
};
//---------------------------------------------------------------------------------------
struct MessageHeader
{
  Command command_;
  Direction dir_;
  uint8_t toClient_;
};
//---------------------------------------------------------------------------------------
struct MessageBody
{
  std::vector<uint8_t> data_;
};
//---------------------------------------------------------------------------------------
struct Error
{
  ErrorCode code_;
};
//---------------------------------------------------------------------------------------
struct Message
{
  MessageHeader header_;
  MessageBody   body_;
};
//---------------------------------------------------------------------------------------
} //protocol
} //server
//---------------------------------------------------------------------------------------
#endif //SERVER_PROTOCOL_HPP
