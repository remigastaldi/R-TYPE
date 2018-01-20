/*
** Server.hpp for R-TYPE
**
** Made by	Tanguy Lelievre
** Login	leliev_t
**
** Started on	Wed Jan 17 21:21:19 2018 Tanguy Lelievre
** Last update	Thu Jan 18 22:35:26 2018 Tanguy Lelievre
*/

#pragma once

#include	"RoomManager.hpp"
#include	"Communication/AsioSyncUdpNetwork.hpp"

class	Server {
public:
  Server();
  ~Server();

  void	acceptClient();
private:
  // RoomManager	_roomManager;
  AsioSyncUdpNetwork	_net;
};
