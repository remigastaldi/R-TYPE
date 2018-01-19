#pragma once

#include <functional>
#include <unordered_map>
#include <boost/asio.hpp>
#include <stdexcept>
#include "ICommunication.hpp"
#include <iostream>

class AsioSyncUdpNetwork : public ICommunication {
public:
  AsioSyncUdpNetwork(int);
  virtual	~AsioSyncUdpNetwork();

  virtual void	connect(const std::string &);
  virtual std::string	receive();
  virtual void	send(const std::string &);
  virtual void	send(const std::string &, const std::string &);
  virtual void  disconnect();

  // virtual	std::string	&getLastSender() const;
private:
  int	_port;
  boost::asio::io_context _context;
  boost::asio::ip::udp::endpoint	_endpoint;
  boost::asio::ip::udp::socket	_socket;
};
