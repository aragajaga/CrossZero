//---------------------------------------------------------------------------------------
#ifndef SERVER_PROTOCOL_HPP
#define SERVER_PROTOCOL_HPP
//---------------------------------------------------------------------------------------
#include <cstdint>
#include <vector>
//---------------------------------------------------------------------------------------
// SERVER PROTOCOL
//
// Server and client sending message according to this protocol
// This protocol contains follows margins:
//   - Message header, which contain:
//     - first byte, which say to server what is this message contain
//     - second byte, which say to server who should receive this message(server, client, all clients)
//     - third byte, which say to server what kind of client should receive this message(if concrete client)
//     - seven bytes reserved for future use
//   - Body of message, which contain stream of bytes
//
// Message header:
//  - first byte may send follows commands:
//    - user message - this message contain normal text, which client enter and send
//    - server message - this message may contain command to server, for example: flush or drop all messages
//    - test message - this message testing, what client still connected(sending by timeout)
//    - command - reserved to server message, can not be used
//  - second byte. It's direction, it define, who receive this message, may contain follows commands:
//    - to server - message intended for server and not sent to other users
//    - to all clients - message intended for all clients, connected to server
//    - to concrete client - message intended for concrete client. who receive this message is definition by the third byte
//  - third byte provide, who concrete receive message, but he's will be filled only if second byte equals to command "to concrete client"
//  - reserved bytes unused yet, but he's should be decoding(just remove from buffer)
//
// All message bodies should be ending on byte, called "endOfMessageByte"
// If it's byte has not be detected, server will be wait other part of bytes.
// Wherein, while server wait other part of bytes, server can't receive others messages.
// More precisely, he's receive this, and if he's contain "endOfMessageByte", then decoding continues!
// Be carefully!!!
//
// To avoid errors, I'm advice follow this manual!
//---------------------------------------------------------------------------------------
namespace server
{
namespace protocol
{
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
  uint8_t reserved[7];
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
constexpr const uint8_t  endOfMessageByte = 0x00;
constexpr const uint32_t minimumToDecodeSize = sizeof(MessageHeader);
//---------------------------------------------------------------------------------------
} //protocol
} //server
//---------------------------------------------------------------------------------------
#endif //SERVER_PROTOCOL_HPP
