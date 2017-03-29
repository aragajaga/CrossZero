//---------------------------------------------------------------------------------------
#ifndef MESSAGE_DECODER_HPP
#define MESSAGE_DECODER_HPP
//---------------------------------------------------------------------------------------
#include "server/common_data.hpp"
#include "server_interfaces.hpp"
#include "server_protocol.hpp"
//---------------------------------------------------------------------------------------
// Standart decoder.
// You can write your decoder, but he's should respond follows demands:
//  - He should have method, called "addDataAndTryToDecode", which can be used for decoding message, if received
//  - He should contain IServerBase interface and call this, when you want send decoding message to server parse.
//---------------------------------------------------------------------------------------
namespace server
{
namespace detail
{
//---------------------------------------------------------------------------------------
class MessageDecoder
{
public:
  MessageDecoder(IServerBase & server);

  void addDataAndTryToDecode(const internal::ContainerByte & data);

private:
  void tryToDecode();

  bool parseBuffer(protocol::Message & msg, protocol::Error & error);

  bool readFirstByte(protocol::Message & msg);
  bool readDirectionByte(protocol::Message & msg);
  void readUserByte(protocol::Message & msg);
  void readReserved(protocol::Message & msg);

  bool makeError(protocol::ErrorCode code, protocol::Error & err);

  internal::ContainerByte buffer_;
  IServerBase & user_;
};
//---------------------------------------------------------------------------------------
} //detail

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
// IMPLEMENTATION
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
detail::MessageDecoder::MessageDecoder(IServerBase & server)
  :
  user_(server)
{}
//---------------------------------------------------------------------------------------
void detail::MessageDecoder::addDataAndTryToDecode(const internal::ContainerByte & data)
{
  auto it = std::find(data.cbegin(), data.cend(), protocol::endOfMessageByte);

  if (it == data.cend())
    std::copy(data.cbegin(), data.cend(), std::back_inserter(buffer_));
  else
  {
    auto prevIt = data.cbegin();

    while(it != data.cend())
    {
      std::copy(prevIt, it, std::back_inserter(buffer_));

      tryToDecode();

      prevIt = it + 1;

      it = std::find(prevIt, data.cend(), protocol::endOfMessageByte);
    }
  }
}
//---------------------------------------------------------------------------------------
void detail::MessageDecoder::tryToDecode()
{
  protocol::Message msg;
  protocol::Error error;

  if (parseBuffer(msg, error))
    user_.onMessage(msg);
  else
    user_.onDecodeError(error);
}
//---------------------------------------------------------------------------------------
bool detail::MessageDecoder::parseBuffer(protocol::Message & msg, protocol::Error & error)
{
  if (buffer_.size() <protocol::minimumToDecodeSize)
    return makeError(protocol::ErrorCode::NoDataForDecoding, error);

  if (!readFirstByte(msg))
    return makeError(protocol::ErrorCode::FirstByteMismatch, error);

  if (!readDirectionByte(msg))
    return makeError(protocol::ErrorCode::DirectionByteMismatch, error);

  readUserByte(msg);

  std::copy(buffer_.begin(), buffer_.end(), std::back_inserter(msg.body_.data_));

  buffer_.clear();
  return true;
}
//---------------------------------------------------------------------------------------
bool detail::MessageDecoder::readFirstByte(protocol::Message & msg)
{
  switch(static_cast<protocol::Command>(buffer_.front()))
  {
    case protocol::Command::UserMessage:
    case protocol::Command::ServerMessage:
    case protocol::Command::TestMessage:
    case protocol::Command::Command:
      msg.header_.command_ = static_cast<protocol::Command>(buffer_.front());
      break;
    default:
      return false;
  }

  buffer_.pop_front();

  return true;
}
//---------------------------------------------------------------------------------------
bool detail::MessageDecoder::readDirectionByte(protocol::Message & msg)
{
  switch(static_cast<protocol::Direction>(buffer_.front()))
  {
    case protocol::Direction::ToServer:
    case protocol::Direction::ToAllClient:
    case protocol::Direction::ToConcreteClient:
      msg.header_.dir_ = static_cast<protocol::Direction>(buffer_.front());
      break;
    default:
      return false;
  }

  buffer_.pop_front();

  return true;
}
//---------------------------------------------------------------------------------------
void detail::MessageDecoder::readUserByte(protocol::Message & msg)
{
  if (msg.header_.dir_ == protocol::Direction::ToConcreteClient)
    msg.header_.toClient_ = buffer_.front();

  buffer_.pop_front();
}
//---------------------------------------------------------------------------------------
bool detail::MessageDecoder::makeError(protocol::ErrorCode code, protocol::Error & err)
{
  buffer_.clear();

  err.code_ = code;

  return false;
}
//---------------------------------------------------------------------------------------
} //server
//---------------------------------------------------------------------------------------
#endif // MESSAGE_DECODER_HPP
//---------------------------------------------------------------------------------------
