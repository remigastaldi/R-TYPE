/*
** Server.cpp for R-TYPE
**
** Made by	Tanguy Lelievre
** Login	leliev_t
**
** Started on	Wed Jan 17 21:20:53 2018 Tanguy Lelievre
** Last update	Sun Jan 21 04:05:07 2018 Tanguy Lelievre
*/

#include <iostream>
#include "Server.hpp"
#include "AlfredBase/Random/Random.hpp"

Server::Server() : _net(8000),
_roomManager(_net)
{

}

Server::~Server()
{

}

std::string	Server::login()
{
  std::string a(Alfred::Random::string(16));
  return (a);
}

void	Server::waitClientPacket()
{
  std::string	msg;

  for (;;)
  {
    msg = _net.receive();
    manageClientPacket(msg);
  }
}

void	Server::manageClientPacket(std::string &msg)
{
  Packet	rpacket(msg, _net.getLastSender());
  if (rpacket.getToken().length() == 0)
  {
    std::string token = login();
    rpacket.setToken(token);
    _roomManager.addPlayer(token);
    _net.send("player ajouté", _net.getLastSender());
  }
  else
  {
    _roomManager.transferRequest(rpacket);
  }
}
