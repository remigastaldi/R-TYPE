/*
** ICommunication.hpp for R-TYPE
**
** Made by	Tanguy Lelievre
** Login	leliev_t
**
** Started on	Sun Jan 14 19:40:10 2018 Tanguy Lelievre
** Last update	Sun Jan 21 20:20:54 2018 Tanguy Lelievre
*/

#pragma once

#include <string>
#include "UDPPacket.hpp"

class ICommunication {
public:
  virtual ~ICommunication() {};

  virtual void	connect(const std::string &) = 0;
  virtual UDPPacket	receive() = 0;
  virtual void	send(UDPPacket &) = 0;
  virtual void  disconnect() = 0;
};
