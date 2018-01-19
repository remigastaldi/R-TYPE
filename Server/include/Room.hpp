/*
** Room.hpp for R-TYPE
**
** Made by	Tanguy Lelievre
** Login	leliev_t
**
** Started on	Wed Jan 17 22:29:28 2018 Tanguy Lelievre
** Last update	Thu Jan 18 22:35:24 2018 Tanguy Lelievre
*/

#pragma once

#include <unordered_map>

class	Room {
public:
  Room();
  ~Room();
private:
  int	_roomId;
  std::unordered_map<std::string, std::string>	_clients;
};
