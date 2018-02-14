/*
** Client.cpp for R-TYPE
**
** Made by	Tanguy Lelievre
** Login	leliev_t
**
** Started on	Mon Jan 22 02:59:41 2018 Tanguy Lelievre
** Last update	Mon Jan 22 13:13:39 2018 Tanguy Lelievre
*/

#include "Client.hpp"

Client::Client() : _ip(""),
_token(""),
_name(""),
_roomId(""),
_ready(false)
{

}

Client::~Client()
{

}

std::string const	&Client::getIp() const
{
  return (_ip);
}

void	Client::setIp(const std::string &ip)
{
  _ip = ip;
}

std::string const	&Client::getToken() const
{
  return (_token);
}

void	Client::setToken(const std::string &token)
{
  _token = token;
}

std::string const	&Client::getName() const
{
  return (_name);
}

void	Client::setName(std::string &name)
{
  _name = name;
}

std::string const	&Client::getRoom() const
{
  return (_roomId);
}

void	Client::setRoom(const std::string &roomId)
{
  _roomId = roomId;
}

bool	Client::getState() const
{
  return (_ready);
}

void	Client::setState(bool state)
{
  _ready = state;
}

unsigned short	Client::getPort() const
{
  return (_port);
}

void	Client::setPort(unsigned short port)
{
  _port = port;
}
