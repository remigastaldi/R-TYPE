/*
** Room.cpp for R-TYPE
**
** Made by	Tanguy Lelievre
** Login	leliev_t
**
** Started on	Mon Jan 22 00:40:59 2018 Tanguy Lelievre
** Last update	Mon Jan 22 05:54:28 2018 Tanguy Lelievre
*/

#include "Room.hpp"

Room::Room(std::shared_ptr<AsioSyncUdpNetwork> &net) : _roomId(""),
_clients(),
_name(""),
_net(net)
{

}

Room::Room(const std::string &roomId, std::shared_ptr<AsioSyncUdpNetwork> &net) : _roomId(roomId),
_clients(),
_name(""),
_net(net)
{

}

Room::~Room()
{

}

std::string const	&Room::getName() const
{
  return (_name);
}

void	Room::setName(const std::string &name)
{
  _name = name;
}

std::string const	&Room::getId() const
{
  return (_roomId);
}

void	Room::setId(const std::string &id)
{
  _roomId = id;
}

void	Room::broadcast(UDPPacket &packet)
{
  std::string	str("player");
  std::string	player;

  for (size_t i = 0; i < 4; i++) {
    player = str + std::to_string((i + 1));
    if (_clients[player].getName().length() != 0 &&
    _clients[player].getToken() != packet.getToken())
    {
      _net.get()->send(packet, _clients[player].getIp());
    }
  }
}

void	Room::addPlayer(Client &client)
{
  std::string	str("player");
  std::string	player;

  for (size_t i = 0; i < 4; i++) {
    player = str + std::to_string((i + 1));
    if (_clients[player].getName().length() == 0)
    {
      _clients[player] = client;
      client.setName(player);
      break;
    }
  }
}

void	Room::removePlayer(Client &client)
{
  std::string	str("player");
  std::string	player;

  for (size_t i = 0; i < 4; i++) {
    player = str + std::to_string((i + 1));
    if (_clients.find(player) != _clients.end() && _clients[player].getToken() == client.getToken())
    {
      _clients.erase(player);
      break;
    }
  }
}

int	Room::getNbPlayer()
{
  int	ret;
  std::string	str("player");
  std::string	player;

  ret = 0;
  for (size_t i = 0; i < 4; i++) {
    player = str + std::to_string((i + 1));
    if (_clients.find(player) != _clients.end() &&
    _clients[player].getName().length() > 0)
      ret++;
  }
  return (ret);
}
