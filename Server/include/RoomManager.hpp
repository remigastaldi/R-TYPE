/*
** RoomManager.hpp for R-TYPE
**
** Made by	Tanguy Lelievre
** Login	leliev_t
**
** Started on	Wed Jan 17 22:09:03 2018 Tanguy Lelievre
** Last update	Sun Jan 21 19:07:32 2018 Tanguy Lelievre
*/

#pragma once

#include "Room.hpp"

class	RoomManager {
public:
RoomManager(AsioSyncUdpNetwork &);
  ~RoomManager();

  void	transferRequest(UDPPacket &);
  // void	joinRoom(std::string &, std::string &);
  void	addPlayer(std::string &);
  // void	createRoom(std::string &);

private:
  std::unordered_map<std::string, Room>	_roomList;
  std::unordered_map<std::string, std::string>	_clientsList;
};
