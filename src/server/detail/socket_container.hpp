//---------------------------------------------------------------------------------------
#ifndef SOCKET_CONTAINER_HPP
#define SOCKET_CONTAINER_HPP
//---------------------------------------------------------------------------------------
#include <vector>
#include <memory>
//---------------------------------------------------------------------------------------
namespace server
{
namespace detail
{
//---------------------------------------------------------------------------------------
template<typename Socket>
class SocketContainer
{
  using SocketPtr = std::shared_ptr<Socket>;

public:

  void pushClient(SocketPtr && newClient);

  SocketPtr getClient(size_t index) const;
  SocketPtr getAtClient(size_t index) const;

private:

  std::vector<SocketPtr> sockets_;
};
//---------------------------------------------------------------------------------------
} //detail
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
// IMPLEMENTATION
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
template<typename Socket>
void detail::SocketContainer<Socket>::pushClient(SocketPtr && newClient)
{
  sockets_.push_back(std::move(newClient));
}
//---------------------------------------------------------------------------------------
template<typename Socket>
typename detail::SocketContainer<Socket>::SocketPtr
  detail::SocketContainer<Socket>::getClient(size_t index) const
{
  return sockets_[index];
}
//---------------------------------------------------------------------------------------
template<typename Socket>
typename detail::SocketContainer<Socket>::SocketPtr
  detail::SocketContainer<Socket>::getAtClient(size_t index) const
{
  if (index < 0 || index >= sockets_.size())
    throw std::out_of_range("out of range socket container");

  return sockets_[index];
}
//---------------------------------------------------------------------------------------
using TcpSocketContainer = detail::SocketContainer<sf::TcpSocket>;
using UdpSocketContainer = detail::SocketContainer<sf::UdpSocket>;
//---------------------------------------------------------------------------------------
} //server
//---------------------------------------------------------------------------------------
#endif // SOCKET_CONTAINER_HPP
//---------------------------------------------------------------------------------------
