/*
** Server.cpp for R-TYPE
**
** Made by	Tanguy Lelievre
** Login	leliev_t
**
** Started on	Wed Jan 17 21:20:53 2018 Tanguy Lelievre
** Last update	Sun Jan 21 20:54:31 2018 Tanguy Lelievre
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
  UDPPacket	packet;
  for (;;)
  {
    packet = _net.receive();
    manageClientPacket(packet);
  }
}

void	Server::manageClientPacket(UDPPacket &packet)
{
  if (packet.getToken().length() == 0)
  {
    std::string token = login();
    packet.setToken(token);
    _roomManager.addPlayer(token);
    std::cout << packet.getCommand() << std::endl;
    _net.send(packet, _net.getLastSender());
  }
  else
  {
    _roomManager.transferRequest(packet);
  }
}
