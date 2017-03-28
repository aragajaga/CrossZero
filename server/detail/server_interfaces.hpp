//---------------------------------------------------------------------------------------
#ifndef SERVER_INTERFACES_HPP
#define SERVER_INTERFACES_HPP
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
} //detail
} //server
//---------------------------------------------------------------------------------------
#endif // SERVER_INTERFACES_HPP
