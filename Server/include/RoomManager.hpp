/*
** RoomManager.hpp for R-TYPE
**
** Made by	Tanguy Lelievre
** Login	leliev_t
**
** Started on	Wed Jan 17 22:09:03 2018 Tanguy Lelievre
** Last update	Thu Jan 18 22:35:19 2018 Tanguy Lelievre
*/

#pragma once

#include "Room.hpp"

class	RoomManager {
public:
  RoomManager();
  ~RoomManager();

  // void	transferRequest(const std::string &, std::string &);

private:
  std::unordered_map<std::string, Room>	_roomList;
};
