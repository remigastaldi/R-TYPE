#pragma once

#include <functional>
#include <unordered_map>
#include <boost/asio.hpp>
#include "ICommunication.hpp"

class AsioSyncUdpNetwork : public ICommunication {
public:
  AsioSyncUdpNetwork(int);
  virtual	~AsioSyncUdpNetwork();

  virtual void	connect(const std::string &);
  virtual std::string	receive();
  virtual void	send(const std::string &);
  virtual void	send(const std::string &, const std::string &);
  virtual void  disconnect();

private:
  int	_port;
  boost::asio::io_service _service;
  boost::asio::ip::udp::socket	_socket;
  boost::asio::ip::udp::endpoint	_endpoint;
};
