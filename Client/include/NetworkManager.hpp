/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-22T10:35:17+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-22T10:56:02+01:00
 */


#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <chrono>

#include  "Communication/AsioSyncUdpNetwork.hpp"
#include  "RFC.hpp"
#include  "EventManager.hpp"

class NetworkManager
{
public:
  NetworkManager(GameEngine::GameManagers &);
  ~NetworkManager();

  void init();
  void keyPressed(sf::Event event);
  void keyRelease(sf::Event event);
  void mainLoop();
  void pingLoop();
  void login();
  void update();
  void playGame();
  void playerReady();

private:
  AsioSyncUdpNetwork    _network;
  GameEngine::GameManagers &_managers;
  std::mutex            _mutex;
  std::vector<UDPPacket> _queue;
  std::string            _token;
};
