/*
** UDPPacket.cpp for R-TYPE
**
** Made by	Tanguy Lelievre
** Login	leliev_t
**
** Started on	Sat Jan 20 16:03:44 2018 Tanguy Lelievre
** Last update	Mon Jan 22 09:36:58 2018 Tanguy Lelievre
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
  return ("");
}

void	UDPPacket::setData(std::string const &key, std::string const &value)
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

void	UDPPacket::setToken(const std::string &token)
{
  _data["token"] = token;
}

RFC::Commands UDPPacket::getCommand() const
{
  if (_data.find("cmd") != _data.end())
    return (static_cast<RFC::Commands>(std::stoi(_data.at("cmd"))));
  return (RFC::Commands::UNKNOWN);
}

RFC::Responses UDPPacket::getResult() const
{
  if (_data.find("res") != _data.end())
    return (static_cast<RFC::Responses>(std::stoi(_data.at("res"))));
  return (RFC::Responses::UNKNOWN);
}

void	UDPPacket::setCommand(RFC::Commands cmd)
{
  _data["cmd"] = std::to_string(static_cast<unsigned int>(cmd));
}

void	UDPPacket::setResult(RFC::Responses res)
{
  _data["res"] = std::to_string(static_cast<unsigned int>(res));
}

int	UDPPacket::getTimestamp() const
{
  return (std::stoi(_data.at("timestamp")));
}

void	UDPPacket::setTimestamp(int timestamp)
{
  _data["timestamp"] = timestamp;
}
