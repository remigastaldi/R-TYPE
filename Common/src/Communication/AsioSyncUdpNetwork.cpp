/*
** AsioSyncUdpNetwork.cpp for R-TYPE
**
** Made by	Tanguy Lelievre
** Login	leliev_t
**
** Started on	Sun Jan 14 22:23:16 2018 Tanguy Lelievre
** Last update	Mon Jan 22 03:20:18 2018 Tanguy Lelievre
*/

#include "Communication/AsioSyncUdpNetwork.hpp"
#include <boost/serialization/unordered_map.hpp>

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

UDPPacket	AsioSyncUdpNetwork::receive()
{
  UDPPacket	packet;
  std::unordered_map<std::string, std::string>	map;
  try {
    std::string archive_data(1024, 0);
    _socket.receive_from(boost::asio::buffer(archive_data), _lastEndpoint);
    std::istringstream archive_stream(archive_data);
    boost::archive::text_iarchive archive(archive_stream);
    archive >> map;
    map["ip"] = _lastEndpoint.address().to_string();
    packet.setData(map);
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
    throw std::runtime_error("Error receive.");
  }
  return (packet);
}

void	AsioSyncUdpNetwork::send(UDPPacket &packet)
{
  try {
    std::ostringstream archive_stream;
    boost::archive::text_oarchive archive(archive_stream);
    archive << packet.getData();
    std::string outbound_data_ = archive_stream.str();

    _socket.send_to(boost::asio::buffer(outbound_data_), _lastEndpoint);
  } catch (std::exception &e) {
    throw std::runtime_error("Error send.");
  }
}

void	AsioSyncUdpNetwork::send(UDPPacket &packet, const std::string &ip)
{
  try {
    std::ostringstream archive_stream;
    boost::archive::text_oarchive archive(archive_stream);
    archive << packet.getData();
    std::string outbound_data_ = archive_stream.str();

    _lastEndpoint.address(boost::asio::ip::address::from_string(ip));
    _socket.send_to(boost::asio::buffer(outbound_data_), _lastEndpoint);
  } catch (std::exception &e) {
    throw std::runtime_error("Error send.");
  }
}

void	AsioSyncUdpNetwork::send(std::unordered_map<std::string, std::string>	&map, const std::string &ip)
{
  UDPPacket	packet;
  packet.setData(map);
  send(packet, ip);
}

void	AsioSyncUdpNetwork::send(std::unordered_map<std::string, std::string>	&map)
{
  UDPPacket	packet;
  packet.setData(map);
  send(packet);
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
