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
  void mainLoop();
  void update();
  void playGame();
  void playerReady();
  
private:
  AsioSyncUdpNetwork    _network;
  EventManager::Manager &_eventManager;
  std::mutex            _mutex;
  std::vector<UDPPacket> _queue;
  std::shared_ptr<std::thread>      _mainLoop;
  std::string            _token;
};
