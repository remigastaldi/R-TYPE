/*
** RoomManager.cpp for R-TYPE
**
** Made by	Tanguy Lelievre
** Login	leliev_t
**
** Started on	Sat Jan 20 22:26:56 2018 Tanguy Lelievre
** Last update	Wed Feb 21 09:50:53 2018 Tanguy Lelievre
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

void	RoomManager::transferRequest(UDPPacket &packet)
{
  std::cout << "transferrequest" << std::endl;
  _mutex.lock();
  if (_clientsList.find(packet.getToken()) != _clientsList.end() &&
  _roomList.find(_clientsList.at(packet.getToken()).getRoom()) != _roomList.end())
  {
    _roomList.at(_clientsList.at(packet.getToken()).getRoom()).broadcast(packet);
  }
  _mutex.unlock();
}

void	RoomManager::addPlayer(const Client &client)
{
  std::cout << "addplayer" << std::endl;
  _mutex.lock();
  _clientsList.emplace(std::make_pair(client.getToken(), client));
  _mutex.unlock();
}

bool	RoomManager::createRoom(const std::string &name)
{
  Room	newRoom(_net);

  if (_roomList.find(name) == _roomList.end())
  {
    newRoom.setName(name);
    newRoom.setId(name);
    _roomList.emplace(std::make_pair(name, newRoom));
    return (true);
  }
  return (false);
}

bool	RoomManager::checkPlayer(const std::string &player)
{
  std::cout << "checkplayer" << std::endl;
  _mutex.lock();
  if (_clientsList.find(player) != _clientsList.end())
  {
    _mutex.unlock();
    return (true);
  }
  _mutex.unlock();
  return (false);
}

bool	RoomManager::joinRoom(const std::string &player, const std::string &roomId)
{
  UDPPacket	resp;

std::cout << "joinroom" << std::endl;
  resp.setToken(player);
  resp.setData("roomId", roomId);
  _mutex.lock();
  if (_clientsList.find(player) != _clientsList.end() &&
  _roomList.find(roomId) != _roomList.end() &&
  _roomList.at(roomId).getNbPlayer() < 4 &&
  _clientsList[player].getRoom() != roomId)
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
    _roomList.at(roomId).getRoomInfo(resp);
    _net.get()->send(resp, _clientsList[player].getIp(), _clientsList[player].getPort());
    resp.setResult(RFC::Responses::PLAYER_JOIN);
    _roomList.at(roomId).broadcast(resp);
    _mutex.unlock();
    return (true);
  }
  resp.setResult(RFC::Responses::FAIL);
  _mutex.unlock();
  return (false);
}

bool	RoomManager::leaveRoom(const std::string &player)
{
  UDPPacket	resp;

std::cout << "leaveroom" << std::endl;
  resp.setToken(player);
  _mutex.lock();
  if (_clientsList.find(player) != _clientsList.end() &&
  _clientsList.at(player).getRoom().length() > 0 &&
  _roomList.find(_clientsList.at(player).getRoom()) != _roomList.end())
  {
    resp.setCommand(RFC::Commands::LEAVE_ROOM);
    resp.setData("name", _clientsList[player].getName());
    if (_clientsList[player].getRoom().length() > 0)
    {
      resp.setResult(RFC::Responses::PLAYER_LEAVE);
      _roomList.at(_clientsList.at(player).getRoom()).broadcast(resp);
      _roomList.at(_clientsList.at(player).getRoom()).removePlayer(_clientsList.at(player));
      resp.setResult(RFC::Responses::SUCCESS);
      _clientsList[player].setRoom("");
    }
    else
    {
      resp.setResult(RFC::Responses::FAIL);
    }
    _net.get()->send(resp, _clientsList[player].getIp(), _clientsList[player].getPort());
    _mutex.unlock();
    return (true);
  }
  _mutex.unlock();
  return (false);
}

void	RoomManager::setPlayerReady(const std::string &player)
{
  UDPPacket	packet;

std::cout << "set player ready" << std::endl;
  packet.setToken(player);
  packet.setCommand(RFC::Commands::READY);
  _mutex.lock();
  if (_clientsList.find(player) != _clientsList.end() &&
  _clientsList.at(player).getRoom().length() > 0 &&
  _roomList.find(_clientsList.at(player).getRoom()) != _roomList.end())
  {
    _roomList.at(_clientsList[player].getRoom()).setPlayerReady(_clientsList[player].getName());
    packet.setResult(RFC::Responses::PLAYER_READY);
    _roomList.at(_clientsList.at(player).getRoom()).getRoomInfo(packet);
    packet.setData("name", _clientsList.at(player).getName());
    _net.get()->send(packet, _clientsList[player].getIp(), _clientsList[player].getPort());
    std::string	str("player");
    std::string	client;
    int	ready;
    ready = 0;
    for (size_t i = 0; i < 4; i++) {
      client = str + std::to_string((i + 1));
      if (packet.getData(client).length() > 0 &&
        packet.getData(client) == "true")
      {
        ready++;
      }
    }
    if (ready == _roomList.at(_clientsList.at(player).getRoom()).getNbPlayer())
    {
        packet.setCommand(RFC::Commands::START_GAME);
        packet.setResult(RFC::Responses::GAME_STARTED);
        _roomList.at(_clientsList.at(player).getRoom()).broadcast(packet);
        _net.get()->send(packet, _clientsList[player].getIp(), _clientsList[player].getPort());
    }
  }
  _mutex.unlock();
}

void	RoomManager::setPlayerTimestamp(UDPPacket &packet)
{
  std::string	player = packet.getToken();

std::cout << "set player timestamp" << std::endl;
  _mutex.lock();
  if (_clientsList.find(player) != _clientsList.end())
    _clientsList.at(player).setTimestamp(packet.getTimestamp());
  _mutex.unlock();
}

void	RoomManager::checkPlayerTimestamp()
{
  for (;;)
  {
    std::cout << "check player timestamp" << std::endl;
    _mutex.lock();
    for (auto it : _clientsList)
    {
      unsigned int ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

      if (ms - it.second.getTimestamp() > 2000)
      {
        _mutex.unlock();
        disconnect(it.second);
        _mutex.lock();
      }
    }
    _mutex.unlock();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  }
}

void	RoomManager::disconnect(Client &player)
{
  std::cout << "disconnect" << std::endl;
  _mutex.lock();
  if (player.getRoom().length() > 0 && _roomList.find(player.getRoom()) != _roomList.end())
  {
    _mutex.unlock();
    leaveRoom(player.getToken());
    _mutex.lock();
  }
  _clientsList.erase(player.getToken());
  _mutex.unlock();
}
