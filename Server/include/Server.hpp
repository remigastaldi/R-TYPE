/*
** Server.hpp for R-TYPE
**
** Made by	Tanguy Lelievre
** Login	leliev_t
**
** Started on	Wed Jan 17 21:21:19 2018 Tanguy Lelievre
** Last update	Sun Jan 21 19:52:32 2018 Tanguy Lelievre
*/

#pragma once

#include	"RoomManager.hpp"

class	Server {
public:
  Server();
  ~Server();

  void	waitClientPacket();
  void	manageClientPacket(UDPPacket &);
  std::string login();
private:
  AsioSyncUdpNetwork	_net;
  RoomManager	_roomManager;

};
