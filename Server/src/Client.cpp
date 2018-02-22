/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-02-15T15:02:12+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-16T10:52:35+01:00
 */


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
_ready(false),
_port(),
_timestamp(0)
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

unsigned int	Client::getTimestamp() const
{
  return (_timestamp);
}

void	Client::setTimestamp(unsigned int timestamp)
{
  _timestamp = timestamp;
}
