/*
** RoomManager.cpp for R-TYPE
**
** Made by	Tanguy Lelievre
** Login	leliev_t
**
** Started on	Sat Jan 20 22:26:56 2018 Tanguy Lelievre
** Last update	Mon Jan 22 05:39:14 2018 Tanguy Lelievre
*/

#include "RoomManager.hpp"

RoomManager::RoomManager(AsioSyncUdpNetwork &net) : _roomList(),
_clientsList(),
_net(&net)
{

}

RoomManager::~RoomManager()
{
}

void	RoomManager::transferRequest(const UDPPacket &packet)
{
  (void) packet;
}

void	RoomManager::addPlayer(const Client &client)
{
  _clientsList.emplace(std::make_pair(client.getToken(), client));
}

bool	RoomManager::createRoom(const std::string &name)
{
  Room	newRoom(_net);

  if (_roomList.find(name) == _roomList.end())
  {
    newRoom.setName(name);
    newRoom.setId(name);
    _roomList.emplace(std::make_pair(name, newRoom));;
    return (true);
  }
  return (false);
}

bool	RoomManager::checkPlayer(const std::string &player)
{
  if (_clientsList.find(player) != _clientsList.end())
    return (true);
  return (false);
}

bool	RoomManager::joinRoom(const std::string &player, const std::string &roomId)
{
  UDPPacket	resp;

  resp.setToken(player);
  resp.setData("roomId", roomId);
  if (_clientsList.find(player) != _clientsList.end() &&
  _roomList.find(roomId) != _roomList.end() &&
  _roomList.at(roomId).getNbPlayer() < 4)
  {
    if (_clientsList[player].getRoom().length() > 0 &&
    _roomList.find(_clientsList[player].getRoom()) != _roomList.end())
    {
      _roomList.at(roomId).removePlayer(_clientsList[player]);
    }
    _roomList.at(roomId).addPlayer(_clientsList[player]);
    _clientsList[player].setRoom(roomId);
    resp.setCommand(RFC::Commands::JOIN_ROOM);
    resp.setResult(RFC::Responses::SUCCESS);
    resp.setData("name", _clientsList[player].getName());
    _net.get()->send(resp);
    _roomList.at(roomId).broadcast(resp);
    return (true);
  }
  resp.setResult(RFC::Responses::FAIL);
  return (false);
}

bool	RoomManager::leaveRoom(std::string &player)
{
  if (_clientsList.find(player) != _clientsList.end() &&
  _clientsList.at(player).getRoom().length() > 0 &&
  _roomList.find(_clientsList.at(player).getRoom()) != _roomList.end())
  {
    if (_clientsList[player].getRoom().length() > 0)
      _roomList.at(_clientsList.at(player).getRoom()).removePlayer(_clientsList.at(player));
    _clientsList[player].setRoom("");
    return (true);
  }
  return (false);
}
