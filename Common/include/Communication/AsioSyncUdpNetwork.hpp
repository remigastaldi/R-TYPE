/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-02-15T15:02:12+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-21T13:15:29+01:00
 */


#pragma once

#include "ICommunication.hpp"
#include "UDPPacket.hpp"

#include <boost/asio.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include <stdexcept>
#include <iostream>
#include <chrono>
#include <unordered_map>

class AsioSyncUdpNetwork : public ICommunication {
public:
  explicit AsioSyncUdpNetwork(int);
  AsioSyncUdpNetwork(int, int);
  virtual	~AsioSyncUdpNetwork();

  virtual void	connect(const std::string &);
  virtual UDPPacket	receive();
  virtual void	send(UDPPacket &);
  virtual void	send(UDPPacket &, const std::string &);
  virtual void	send(UDPPacket &, const std::string &, unsigned short);
  // virtual void	send(std::unordered_map<std::string, std::string>	&, const std::string &);
  // virtual void	send(std::unordered_map<std::string, std::string>	&);
  virtual void  disconnect();

  virtual	const std::string	getLastSender() const;

  std::unordered_map<std::string, std::string>  serializeStringToUnorderedMap(std::string string);
  std::string deserializeUnorderedMapToString(const std::unordered_map<std::string, std::string> &map);
private:
  int	_port;
  boost::asio::io_context _context;
  boost::asio::ip::udp::endpoint	_endpoint;
  boost::asio::ip::udp::socket	_socket;
  boost::asio::ip::udp::endpoint	_lastEndpoint;
};
