/*
** AsioSyncUdpNetwork.cpp for R-TYPE
**
** Made by	Tanguy Lelievre
** Login	leliev_t
**
** Started on	Sun Jan 14 22:23:16 2018 Tanguy Lelievre
** Last update	Sun Jan 21 05:44:38 2018 Tanguy Lelievre
*/

#include "Communication/AsioSyncUdpNetwork.hpp"

AsioSyncUdpNetwork::AsioSyncUdpNetwork(int port) :
_port(port),
_context(),
_endpoint(boost::asio::ip::udp::v4(), _port),
_socket(_context, _endpoint),
_lastEndpoint()
{
}

AsioSyncUdpNetwork::AsioSyncUdpNetwork(int port, int serverPort) :
_port(port),
_context(),
_endpoint(boost::asio::ip::udp::v4(), _port),
_socket(_context, _endpoint),
_lastEndpoint(boost::asio::ip::udp::v4(), serverPort)
{
}

AsioSyncUdpNetwork::~AsioSyncUdpNetwork()
{
}

void	AsioSyncUdpNetwork::connect(const std::string &port)
{
  if (_socket.is_open() == true) {
    return;
  }
  _port = std::stoi(port);
}

std::string	AsioSyncUdpNetwork::receive()
{
  std::string msg(1024, 0);

  try {
    _socket.receive_from(boost::asio::buffer(msg), _lastEndpoint);
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
    throw std::runtime_error("Error receive.");
  }
  return (msg);
}

void	AsioSyncUdpNetwork::send(const std::string &msg)
{
  try {
    _socket.send_to(boost::asio::buffer(msg), _endpoint);
  } catch (std::exception &e) {
    throw std::runtime_error("Error send.");
  }
}

void	AsioSyncUdpNetwork::send(const std::string &msg, const std::string &ip)
{
  try {
    _lastEndpoint.address(boost::asio::ip::address::from_string(ip));
    _socket.send_to(boost::asio::buffer(msg), _lastEndpoint);
  } catch (std::exception &e) {
    throw std::runtime_error("Error send.");
  }
}

void  AsioSyncUdpNetwork::disconnect()
{
  if (_socket.is_open() == true)
    _socket.close();
}

std::string	AsioSyncUdpNetwork::getLastSender() const
{
  return (_lastEndpoint.address().to_string());
}
