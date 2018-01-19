/*
** AsioSyncUdpNetwork.cpp for R-TYPE
**
** Made by	Tanguy Lelievre
** Login	leliev_t
**
** Started on	Sun Jan 14 22:23:16 2018 Tanguy Lelievre
** Last update	Sat Jan 20 00:35:22 2018 Tanguy Lelievre
*/

#include "Communication/AsioSyncUdpNetwork.hpp"

AsioSyncUdpNetwork::AsioSyncUdpNetwork(int port) : _port(port), _context(), _endpoint(boost::asio::ip::udp::v4(), _port), _socket(_context, _endpoint)
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
  std::string msg;
  boost::asio::ip::udp::endpoint	nend;

  try {
    _socket.receive_from(boost::asio::buffer(msg), nend);
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
    _endpoint.address(boost::asio::ip::address::from_string(ip));
    _socket.send_to(boost::asio::buffer(msg), _endpoint);
  } catch (std::exception &e) {
    throw std::runtime_error("Error send.");
  }
}

void  AsioSyncUdpNetwork::disconnect()
{
  if (_socket.is_open() == true)
    _socket.close();
}
