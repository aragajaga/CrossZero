//---------------------------------------------------------------------------------------
#include <algorithm>
//---------------------------------------------------------------------------------------
#include "server.hpp"
//---------------------------------------------------------------------------------------
namespace server
{
namespace detail
{
//---------------------------------------------------------------------------------------
void MessageDecoder::addDataAndTryToDecode(const internal::ContainerByte & data)
{
  auto it = std::find(data.cbegin(), data.cend(), protocol::endOfMessage);

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

      it = std::find(prevIt, data.cend(), protocol::endOfMessage);
    }
  }
}
//---------------------------------------------------------------------------------------
void MessageDecoder::tryToDecode()
{
  protocol::Message msg;
  protocol::Error error;

  if (parseBuffer(msg, error))
    user_.onMessage(msg);
  else
    user_.onDecodeError(error);
}
//---------------------------------------------------------------------------------------
bool MessageDecoder::parseBuffer(protocol::Message & msg, protocol::Error & error)
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
bool MessageDecoder::readFirstByte(protocol::Message & msg)
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
bool MessageDecoder::readDirectionByte(protocol::Message & msg)
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
void MessageDecoder::readUserByte(protocol::Message & msg)
{
  msg.header_.toClient_ = buffer_.front();
  buffer_.pop_front();
}
//---------------------------------------------------------------------------------------
bool MessageDecoder::makeError(protocol::ErrorCode code, protocol::Error & err)
{
  buffer_.clear();

  err.code_ = code;

  return false;
}
//---------------------------------------------------------------------------------------
} //detail
} //server
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
