/*
** RoomManager.hpp for R-TYPE
**
** Made by	Tanguy Lelievre
** Login	leliev_t
**
** Started on	Wed Jan 17 22:09:03 2018 Tanguy Lelievre
** Last update	Mon Jan 22 07:20:26 2018 Tanguy Lelievre
*/

#pragma once

#include "Room.hpp"
#include "AlfredBase/Random/Random.hpp"

class	RoomManager {
public:
RoomManager(AsioSyncUdpNetwork &);
  ~RoomManager();

  void	transferRequest(UDPPacket &);
  bool	joinRoom(const std::string &, const std::string &);
  bool	leaveRoom(std::string &);
  void	addPlayer(const Client &);
  bool	createRoom(const std::string &);
  bool	checkPlayer(const std::string &);
  void	setPlayerReady(const std::string &);
private:
  std::unordered_map<std::string, Room>	_roomList;
  std::unordered_map<std::string, Client>	_clientsList;
  std::shared_ptr<AsioSyncUdpNetwork>	_net;
};
