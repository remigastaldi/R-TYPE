/*
** Server.cpp for R-TYPE
**
** Made by	Tanguy Lelievre
** Login	leliev_t
**
** Started on	Wed Jan 17 21:20:53 2018 Tanguy Lelievre
** Last update	Sat Jan 20 00:25:31 2018 Tanguy Lelievre
*/

#include <iostream>
#include "Server.hpp"

Server::Server() : _net(8000)
{

}

Server::~Server()
{

}

void	Server::acceptClient()
{
  std::string	msg;

  msg = _net.receive();
  std::cout << "bonjour" << std::endl;
}
