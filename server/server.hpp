//---------------------------------------------------------------------------------------
// Server for CrossZero
// Created by GbaLog
// Link on github.com: https://github.com/GbaLog
//---------------------------------------------------------------------------------------
// TODO:
// - add messages handler
// - add errors handler
// - add server
//---------------------------------------------------------------------------------------
#ifndef SERVER_HPP
#define SERVER_HPP
//---------------------------------------------------------------------------------------
#include <SFML/Network.hpp>
//---------------------------------------------------------------------------------------
#include "detail/server_protocol.hpp"
#include "detail/server_interfaces.hpp"
#include "detail/message_decoder.hpp"
#include "detail/socket_container.hpp"
#include "server_listener.hpp"
#include "server_connection_mng.hpp"
//---------------------------------------------------------------------------------------
namespace server
{
//---------------------------------------------------------------------------------------
using TcpSocketContainer = detail::SocketContainer<sf::TcpSocket>;
using UdpSocketContainer = detail::SocketContainer<sf::UdpSocket>;
//---------------------------------------------------------------------------------------
} //server
//---------------------------------------------------------------------------------------
#endif //SERVER_HPP
//---------------------------------------------------------------------------------------
