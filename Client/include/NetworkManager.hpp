#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include  "Communication/AsioSyncUdpNetwork.hpp"
#include  "RFC.hpp"
#include  "EventManager.hpp"

class NetworkManager
{
public:
  NetworkManager(EventManager::Manager &);
  ~NetworkManager();

  void init();
  void keyPressed(sf::Event event);

private:
  EventManager::Manager &_eventManager;
  AsioSyncUdpNetwork _network;
};
