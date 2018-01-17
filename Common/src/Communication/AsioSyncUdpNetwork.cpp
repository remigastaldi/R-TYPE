/*
** AsioSyncUdpNetwork.cpp for R-TYPE
**
** Made by	Tanguy Lelievre
** Login	leliev_t
**
** Started on	Sun Jan 14 22:23:16 2018 Tanguy Lelievre
** Last update	Wed Jan 17 00:31:25 2018 Tanguy Lelievre
*/

#include "Communication/AsioSyncUdpNetwork.hpp"

AsioSyncUdpNetwork::AsioSyncUdpNetwork(int port) : _service(), _socket(_service), _endpoint(boost::asio::ip::udp::v4(), port) {
  _port = port;
}

AsioSyncUdpNetwork::~AsioSyncUdpNetwork() {
  if (_socket.is_open() == true)
    _socket.close();
}

void	AsioSyncUdpNetwork::connect(const std::string &port) {
  if (_socket.is_open() == true) {
    return;
  }
  _port = std::stoi(port);
}

std::string	AsioSyncUdpNetwork::receive() {
  std::string msg;
  try {
    _socket.receive_from(boost::asio::buffer(msg), _endpoint);
  } catch (boost::system::system_error e) {
    throw std::exception("Error receive.");
  }
  return (msg);
}

void	AsioSyncUdpNetwork::send(const std::string &msg) {
  try {
    _socket.send_to(boost::asio::buffer(msg), _endpoint);
  } catch (boost::system::system_error e) {
    throw std::exception("Error send.");
  }
}

void	AsioSyncUdpNetwork::send(const std::string &msg, const std::string &ip) {
  try {
    _endpoint.address(boost::asio::ip::address::from_string(ip));
    _socket.send_to(boost::asio::buffer(msg), _endpoint);
  } catch (boost::system::system_error e) {
    throw std::exception("Error send.");
  }
}

void  AsioSyncUdpNetwork::disconnect() {
  if (_socket.is_open() == true)
    _socket.close();
}
