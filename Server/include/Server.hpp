/*
** Server.hpp for R-TYPE
**
** Made by	Tanguy Lelievre
** Login	leliev_t
**
** Started on	Wed Jan 17 21:21:19 2018 Tanguy Lelievre
** Last update	Mon Jan 22 07:08:52 2018 Tanguy Lelievre
*/

#pragma once

#include	"RoomManager.hpp"

class	Server {
public:
  Server();
  ~Server();

  void	waitClientPacket();
  void	manageClientPacket(UDPPacket &);
  void	pingClient(UDPPacket &);
  void	loginClient(UDPPacket &);
  void	pressKeyClient(UDPPacket &);
  void	sendResponseToClient(UDPPacket &);
  void	joinRoomClient(UDPPacket &);
  void	createRoomClient(UDPPacket &);
  void	setPlayerReady(UDPPacket &);
private:
  AsioSyncUdpNetwork	_net;
  RoomManager	_roomManager;
};
