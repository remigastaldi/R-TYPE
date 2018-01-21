/*
** Packet.cpp for R-TYPE
**
** Made by	Tanguy Lelievre
** Login	leliev_t
**
** Started on	Sat Jan 20 16:03:44 2018 Tanguy Lelievre
** Last update	Sun Jan 21 01:46:17 2018 Tanguy Lelievre
*/

#include <iostream>
#include "Communication/Packet.hpp"

Packet::Packet() : _data()
{
}

Packet::Packet(std::string &udpPacket, const std::string &ip) : _data()
{
  std::string delimiter = "&";
  std::string equal = "=";
  std::string	key;
  size_t pos = 0;
  std::string token;

  _data["ip"] = ip;
  while ((pos = udpPacket.find(delimiter)) != std::string::npos)
  {
    token = udpPacket.substr(0, pos);
    udpPacket.erase(0, pos + delimiter.length());
    pos = token.find(equal);
    if (pos != std::string::npos) {
      key = token.substr(0, pos);
      token.erase(0, pos + equal.length());
      _data[key] = token;
    }
  }
  pos = udpPacket.find(equal);
  if (pos != std::string::npos) {
    key = udpPacket.substr(0, pos);
    udpPacket.erase(0, pos + equal.length());
    _data[key] = udpPacket;
  }
}

Packet::~Packet()
{
}

std::string	const &Packet::getIp() const
{
  return (_data.at("ip"));
}

void	Packet::setIp(std::string &ip)
{
  _data["ip"] = ip;
}


std::unordered_map<std::string, std::string>	const &Packet::getData() const
{
  return (_data);
}

void	Packet::setData(std::unordered_map<std::string, std::string> &data)
{
  _data = data;
}


std::string	Packet::getData(const std::string &key) const
{
  if (_data.find(key) != _data.end())
    return (_data.at(key));
  return (nullptr);
}

void	Packet::setData(std::string &key, std::string &value)
{
  _data[key] = value;
}

std::string const &Packet::getToken()
{
  return (_data["token"]);
}

void	Packet::setToken(std::string &token)
{
  _data["token"] = token;
}

std::string	const &Packet::getCommand() const
{
  return (_data.at("cmd"));
}

void	Packet::setCommand(std::string &cmd)
{
  _data["cmd"] = cmd;
}

int	Packet::getTimestamp() const
{
  return (std::stoi(_data.at("timestamp")));
}

void	Packet::setTimestamp(int timestamp)
{
  _data["timestamp"] = timestamp;
}
