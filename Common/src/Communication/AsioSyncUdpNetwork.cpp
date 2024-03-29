/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-22T06:10:40+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-21T13:22:05+01:00
 */


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
  if (_socket.is_open() == true) {
    _socket.close();
  }
}

void AsioSyncUdpNetwork::connect(const std::string &port)
{
  if (_socket.is_open() == true) {
    return;
  }
  _port = std::stoi(port);
}

UDPPacket AsioSyncUdpNetwork::receive()
{
  UDPPacket packet;
  try {
    std::string archive_data(1024, 0);
    _socket.receive_from(boost::asio::buffer(archive_data), _lastEndpoint);
    // std::istringstream archive_stream(archive_data);
    // boost::archive::text_iarchive archive(archive_stream);
    // archive >> map;
    std::unordered_map<std::string, std::string> map = serializeStringToUnorderedMap(archive_data);
    map["ip"] = _lastEndpoint.address().to_string();
    map["port"] = std::to_string(_lastEndpoint.port());
    packet.setData(map);
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
    throw std::runtime_error("Error receive.");
  }
  return (packet);
}

void AsioSyncUdpNetwork::send(UDPPacket &packet)
{
  try {
    unsigned int ms = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::system_clock::now().time_since_epoch()).count();
    packet.setTimestamp(std::to_string(ms));
    std::cout << "send : ";
    for (auto it : packet.getData())
      std::cout << " " << it.first << ":" << it.second;
    std::cout << std::endl;
    // std::ostringstream archive_stream;
    // boost::archive::text_oarchive archive(archive_stream);
    // archive << packet.getData();
    // std::string outbound_data_ = archive_stream.str();
    std::string outbound_data_(deserializeUnorderedMapToString(packet.getData()));
    _socket.send_to(boost::asio::buffer(outbound_data_), _lastEndpoint);
    std::cout << "sent to " << _lastEndpoint.address().to_string() << " on port " << _lastEndpoint.port() << std::endl;
  } catch (std::exception &e) {
    throw std::runtime_error("Error send.");
  }
}

void AsioSyncUdpNetwork::send(UDPPacket &packet, const std::string &ip)
{
  try {
    unsigned int ms = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::system_clock::now().time_since_epoch()).count();
    packet.setTimestamp(std::to_string(ms));
    std::cout << "send : ";
    for (auto it : packet.getData())
      std::cout << " " << it.first << ":" << it.second;
    std::cout << std::endl;
    // std::ostringstream archive_stream;
    // boost::archive::text_oarchive archive(archive_stream);
    // archive << packet.getData();
    // std::string outbound_data_ = archive_stream.str();
    std::string outbound_data_(deserializeUnorderedMapToString(packet.getData()));
    _lastEndpoint.address(boost::asio::ip::address::from_string(ip));
    _socket.send_to(boost::asio::buffer(outbound_data_), _lastEndpoint);
    std::cout << "sent to " << _lastEndpoint.address().to_string() << " on port " << _lastEndpoint.port() << std::endl;
  } catch (std::exception &e) {
    throw std::runtime_error("Error send.");
  }
}

void AsioSyncUdpNetwork::send(UDPPacket &packet, const std::string &ip, unsigned short port)
{
  try {
    unsigned int ms = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::system_clock::now().time_since_epoch()).count();
    packet.setTimestamp(std::to_string(ms));
    std::cout << "send : ";
    for (auto it : packet.getData())
      std::cout << " " << it.first << ":" << it.second;
    std::cout << std::endl;
    // std::ostringstream archive_stream;
    // boost::archive::text_oarchive archive(archive_stream);
    // archive << packet.getData();
    // std::string outbound_data_ = archive_stream.str();
    std::string outbound_data_(deserializeUnorderedMapToString(packet.getData()));
    _lastEndpoint.address(boost::asio::ip::address::from_string(ip));
    _lastEndpoint.port(port);
    _socket.send_to(boost::asio::buffer(outbound_data_), _lastEndpoint);
    std::cout << "sent to " << _lastEndpoint.address().to_string() << " on port " << _lastEndpoint.port() << std::endl;
  } catch (std::exception &e) {
    throw std::runtime_error("Error send.");
  }
}

// void	AsioSyncUdpNetwork::send(std::unordered_map<std::string, std::string>	&map, const std::string &ip)
// {
//   UDPPacket	packet;
//   packet.setData(map);
//   send(packet, ip);
// }
//
// void	AsioSyncUdpNetwork::send(std::unordered_map<std::string, std::string>	&map)
// {
//   UDPPacket	packet;
//   packet.setData(map);
//   send(packet);
// }


void AsioSyncUdpNetwork::disconnect()
{
  if (_socket.is_open() == true)
    _socket.close();
}

const std::string AsioSyncUdpNetwork::getLastSender() const
{
  return (_lastEndpoint.address().to_string());
}

 std::unordered_map<std::string, std::string>  AsioSyncUdpNetwork::serializeStringToUnorderedMap(std::string string)
 {
   std::unordered_map<std::string, std::string> map;

   size_t posSecond = 0;
   while ((posSecond = string.find(":")) != std::string::npos)
   {
     std::string second = string.substr(0, posSecond);
     size_t posFirst = second.find("=");
     std::string first = second.substr(0, posFirst);
     second.erase(0, posFirst + 1);
     map[first] = second;
     string.erase(0, posSecond + 1);
   }
   return (map);
 }

std::string AsioSyncUdpNetwork::deserializeUnorderedMapToString(const std::unordered_map<std::string, std::string> &map)
{
  std::string string;

  for (auto it = map.cbegin(); it != map.cend();)
  {
   string += it->first;
   string += "=";
   string += it->second;
   it = std::next(it);
   string += ":";
  }
  return (string);
}
