/*
** Room.hpp for R-TYPE
**
** Made by	Tanguy Lelievre
** Login	leliev_t
**
** Started on	Wed Jan 17 22:29:28 2018 Tanguy Lelievre
** Last update	Wed Feb 21 08:37:26 2018 Tanguy Lelievre
*/

#pragma once

#include <unordered_map>
#include <memory>
#include <thread>
#include	"Communication/AsioSyncUdpNetwork.hpp"
#include "Client.hpp"

class	Room {
public:
  Room(std::shared_ptr<AsioSyncUdpNetwork> &);
  Room(const std::string &, std::shared_ptr<AsioSyncUdpNetwork> &);
  ~Room();

  std::string const	&getName() const;
  void	setName(const std::string &);

  std::string const	&getId() const;
  void	setId(const std::string &);

  void	broadcast(UDPPacket &);

  void	addPlayer(Client &);
  void	removePlayer(Client &);

  int		getNbPlayer();
  void	setPlayerReady(const std::string &);

  void	getRoomInfo(UDPPacket &) const;
private:
  std::string	_roomId;
  std::unordered_map<std::string, Client>	_clients;
  std::string	_name;
  std::shared_ptr<AsioSyncUdpNetwork> _net;
};
