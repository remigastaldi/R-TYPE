/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-17T04:02:41+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-21T22:10:01+01:00
 */


#pragma once

#include  "config.hpp"

#include "SoundManager.hpp"
#include  "ResourcesManager.hpp"
#include  "ECS/Systems/CommonSystems.hpp"
#include  "ECS/Manager.hpp"
#include  "GUIManager.hpp"
#include  "Logger/Logger.hpp"
#include  "EventManager.hpp"
#include  "ECS/Components/Components.hpp"
#include  "ECS/Systems/ClientSystems.hpp"
#include  "Communication/AsioSyncUdpNetwork.hpp"

#include  "StartPage/StartPage.hpp"
#include "LobbyPlayer.hpp"
#include "Ship.hpp"

#include  <chrono>
#include  <cmath>

namespace GameEngine
{
  struct GameManagers
  {
    GameManagers(ResourcesManager &_resourcesManager, EventManager::Manager &_eventManager,
      ECS::Manager &_ecsManager, SoundManager &_soundManager)
      : resourcesManager(_resourcesManager),
      eventManager(_eventManager),
      ecsManager(_ecsManager),
      soundManager(_soundManager)
    {}

    ResourcesManager  &resourcesManager;
    EventManager::Manager &eventManager;
    ECS::Manager    &ecsManager;
    SoundManager    &soundManager;
  };

  class Client
  {
  public:
    Client(const std::string &ip, sf::VideoMode &videoMode);

    void  init(void);
    void  run(void);

    void  update(void);
    void  handleEvents(void);
    void  render(float alpha);

    void  playGame(const std::string &);
    void  exitGame(const std::string &);

  private:
    EventManager::Manager _eventManager;
    ResourcesManager  _resourcesManager;
    ECS::Manager      _ecsManager;
    GUI::Manager      _guiManager;
    AsioSyncUdpNetwork _network;
    SoundManager  _soundManager;
    // SceneManager   _sceneManager;
    // LibraryLoader _libraryLoader;
    // Network _network;

  private:
    std::shared_ptr<Ship> _ship;

    sf::RenderWindow _window;

    std::string _ip;

    double  _gameEngineTick;
    double  _maxFrameRate;
    bool    _running;
  };
}
