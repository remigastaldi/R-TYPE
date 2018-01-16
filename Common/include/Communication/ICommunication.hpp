/*
** ICommunication.hpp for R-TYPE
**
** Made by	Tanguy Lelievre
** Login	leliev_t
**
** Started on	Sun Jan 14 19:40:10 2018 Tanguy Lelievre
** Last update	Wed Jan 17 00:31:38 2018 Tanguy Lelievre
*/

#pragma once

#include <string>

class ICommunication {
public:
  virtual ~ICommunication() = 0;

  virtual void	connect(const std::string &) = 0;
  virtual std::string	receive() = 0;
  virtual void	send(const std::string &) = 0;
  virtual void  disconnect() = 0;
};
