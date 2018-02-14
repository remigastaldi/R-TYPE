#pragma once

#include <stdexcept>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include "ICommunication.hpp"
#include "UDPPacket.hpp"

class AsioSyncUdpNetwork : public ICommunication {
public:
  AsioSyncUdpNetwork(int);
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

  virtual	std::string	getLastSender() const;
private:
  int	_port;
  boost::asio::io_context _context;
  boost::asio::ip::udp::endpoint	_endpoint;
  boost::asio::ip::udp::socket	_socket;
  boost::asio::ip::udp::endpoint	_lastEndpoint;
};
