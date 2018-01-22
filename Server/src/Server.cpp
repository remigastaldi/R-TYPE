/*
** Server.cpp for R-TYPE
**
** Made by	Tanguy Lelievre
** Login	leliev_t
**
** Started on	Wed Jan 17 21:20:53 2018 Tanguy Lelievre
** Last update	Mon Jan 22 09:06:56 2018 Tanguy Lelievre
*/

#include <iostream>
#include "Server.hpp"

Server::Server() : _net(8000),
_roomManager(_net)
{

}

Server::~Server()
{

}

void	Server::waitClientPacket()
{
  UDPPacket	packet;
  for (;;)
  {
    packet = _net.receive();
    manageClientPacket(packet);
  }
}

void	Server::manageClientPacket(UDPPacket &packet)
{
  switch (packet.getCommand()) {
    case RFC::Commands::PING:
      pingClient(packet);
      break;
    case RFC::Commands::LOGIN:
      loginClient(packet);
      break;
    case RFC::Commands::GET_FRIENDS:
      break;
    case RFC::Commands::GET_PROFIL:
      break;
    case RFC::Commands::GET_SHIP_INFO:
      break;
    case RFC::Commands::BUY_SHIP_COMPONENT:
      break;
    case RFC::Commands::SEARCH_ROOM:
      break;
    case RFC::Commands::JOIN_ROOM:
      joinRoomClient(packet);
      break;
    case RFC::Commands::GET_ROOM_INFO:
      break;
    case RFC::Commands::LEAVE_ROOM:
      break;
    case RFC::Commands::READY:
      setPlayerReady(packet);
      break;
    case RFC::Commands::NOT_READY:
      break;
    case RFC::Commands::START_GAME:
      break;
    case RFC::Commands::SELECT_ROOM_LEVEL:
      break;
    case RFC::Commands::CREATE_ROOM:
      createRoomClient(packet);
      break;
    case RFC::Commands::KEY_PRESSED:
      pressKeyClient(packet);
      break;
  }
}

void	Server::pingClient(UDPPacket &packet)
{
  packet.setResult(RFC::Responses::PONG);
  sendResponseToClient(packet);
}

void	Server::loginClient(UDPPacket &packet)
{
  UDPPacket	resp;
  Client	client;

  std::string token(Alfred::Random::string(16));
  while (_roomManager.checkPlayer(token) == true)
    token = Alfred::Random::string(16);
  resp.setToken(token);
  resp.setResult(RFC::Responses::SUCCESS);
  resp.setCommand(RFC::Commands::LOGIN);
  client.setIp(packet.getIp());
  client.setToken(token);
  _roomManager.addPlayer(client);
  std::cout << "Client login successful. Token : " << token << std::endl;
  sendResponseToClient(resp);
}

void	Server::joinRoomClient(UDPPacket &packet)
{
  _roomManager.joinRoom(packet.getToken(), packet.getData("roomId"));
}

void	Server::pressKeyClient(UDPPacket &packet)
{
  packet.setResult(RFC::Responses::SUCCESS);
  std::cout << "Key pressed. Code : " << packet.getData("key") << std::endl;
  sendResponseToClient(packet);
}

void	Server::createRoomClient(UDPPacket &packet)
{
  if (_roomManager.createRoom(packet.getData("roomId")) == true)
  {
    std::cout << "Room created successfully. Room name : " << packet.getData("roomId") << std::endl;
    packet.setResult(RFC::Responses::ROOM_CREATED);
  }
  else
  {
    std::cout << "Failed to create the room. Room name : " << packet.getData("roomId") << std::endl;
    packet.setResult(RFC::Responses::FAIL);
  }
  sendResponseToClient(packet);
}

void	Server::setPlayerReady(UDPPacket &packet)
{
  _roomManager.setPlayerReady(packet.getToken());
}

void	Server::sendResponseToClient(UDPPacket &packet)
{
  _net.send(packet);
}
