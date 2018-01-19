/*
** ICommunication.hpp for R-TYPE
**
** Made by	Tanguy Lelievre
** Login	leliev_t
**
** Started on	Sun Jan 14 19:40:10 2018 Tanguy Lelievre
** Last update	Sat Jan 20 00:08:24 2018 Tanguy Lelievre
*/

#pragma once

#include <string>

class ICommunication {
public:
  virtual ~ICommunication() {};

  virtual void	connect(const std::string &) = 0;
  virtual std::string	receive() = 0;
  virtual void	send(const std::string &) = 0;
  virtual void  disconnect() = 0;
};
