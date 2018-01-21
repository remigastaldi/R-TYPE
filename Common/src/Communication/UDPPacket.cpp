/*
** UDPPacket.cpp for R-TYPE
**
** Made by	Tanguy Lelievre
** Login	leliev_t
**
** Started on	Sat Jan 20 16:03:44 2018 Tanguy Lelievre
** Last update	Sun Jan 21 20:45:42 2018 Tanguy Lelievre
*/

#include <iostream>
#include "Communication/UDPPacket.hpp"

UDPPacket::UDPPacket() : _data()
{
}

UDPPacket::~UDPPacket()
{
}

std::string	const &UDPPacket::getIp() const
{
  return (_data.at("ip"));
}

void	UDPPacket::setIp(std::string &ip)
{
  _data["ip"] = ip;
}


std::unordered_map<std::string, std::string>	const &UDPPacket::getData() const
{
  return (_data);
}

void	UDPPacket::setData(std::unordered_map<std::string, std::string> &data)
{
  _data = data;
}


std::string	UDPPacket::getData(const std::string &key) const
{
  if (_data.find(key) != _data.end())
    return (_data.at(key));
  return (nullptr);
}

void	UDPPacket::setData(std::string &key, std::string &value)
{
  _data[key] = value;
}

void	UDPPacket::deleteData(std::string &key)
{
  if (_data.find(key) != _data.end())
    _data.erase(key);
}

std::string const &UDPPacket::getToken()
{
  return (_data["token"]);
}

void	UDPPacket::setToken(std::string &token)
{
  _data["token"] = token;
}

RFC::Commands UDPPacket::getCommand() const
{
  return (static_cast<RFC::Commands>(_data.at("cmd")[0]));
}

RFC::Commands UDPPacket::getResult() const
{
  return (static_cast<RFC::Commands>(_data.at("res")[0]));
}

void	UDPPacket::setCommand(std::string &cmd)
{
  _data["cmd"] = cmd;
}

int	UDPPacket::getTimestamp() const
{
  return (std::stoi(_data.at("timestamp")));
}

void	UDPPacket::setTimestamp(int timestamp)
{
  _data["timestamp"] = timestamp;
}
