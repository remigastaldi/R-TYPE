/*
** Client.hpp for R-TYPE
**
** Made by	Tanguy Lelievre
** Login	leliev_t
**
** Started on	Mon Jan 22 02:54:04 2018 Tanguy Lelievre
** Last update	Wed Feb 21 00:59:12 2018 Tanguy Lelievre
*/

#pragma once

#include <string>

class	Client
{
public:
  Client();
  ~Client();

  std::string const	&getIp() const;
  void	setIp(const std::string &);

  std::string const	&getToken() const;
  void	setToken(const std::string &);

  std::string const	&getName() const;
  void	setName(std::string &);

  std::string const	&getRoom() const;
  void	setRoom(const std::string &);

  bool	getState() const;
  void	setState(bool);

  unsigned short	getPort() const;
  void	setPort(unsigned short);

  unsigned int	getTimestamp() const;
  void	setTimestamp(unsigned int);

private:
  std::string	_ip;
  std::string	_token;
  std::string	_name;
  std::string	_roomId;
  bool	_ready;
  unsigned short	_port;
  unsigned int	_timestamp;
};
