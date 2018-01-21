/*
** RoomManager.cpp for R-TYPE
**
** Made by	Tanguy Lelievre
** Login	leliev_t
**
** Started on	Sat Jan 20 22:26:56 2018 Tanguy Lelievre
** Last update	Sun Jan 21 03:17:30 2018 Tanguy Lelievre
*/

#include "RoomManager.hpp"

RoomManager::RoomManager(AsioSyncUdpNetwork &) : _roomList(),
_clientsList()
{

}

RoomManager::~RoomManager()
{
}

void	RoomManager::transferRequest(Packet &packet)
{
}

void	RoomManager::addPlayer(std::string &player)
{
  _clientsList[player] = "";
}
