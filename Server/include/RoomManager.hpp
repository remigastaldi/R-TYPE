/*
** RoomManager.hpp for R-TYPE
**
** Made by	Tanguy Lelievre
** Login	leliev_t
**
** Started on	Wed Jan 17 22:09:03 2018 Tanguy Lelievre
** Last update	Wed Feb 21 03:18:04 2018 Tanguy Lelievre
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
  bool	leaveRoom(const std::string &);
  void	addPlayer(const Client &);
  bool	createRoom(const std::string &);
  bool	checkPlayer(const std::string &);
  void	setPlayerReady(const std::string &);
  void	setPlayerTimestamp(UDPPacket &);
  void	checkPlayerTimestamp();
  void	disconnect(Client &);
private:
  std::unordered_map<std::string, Room>	_roomList;
  std::unordered_map<std::string, Client>	_clientsList;
  std::shared_ptr<AsioSyncUdpNetwork>	_net;
  std::mutex	_mutex;
};
