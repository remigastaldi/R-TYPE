/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-17T04:02:41+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-20T02:36:25+01:00
 */


#pragma once

#include  "config.hpp"

#include  "ResourcesManager.hpp"
#include  "ECS/Systems/CommonSystems.hpp"
#include  "ECS/Manager.hpp"
#include  "GUIManager.hpp"
#include  "Logger/Logger.hpp"
#include  "EventManager.hpp"

#include  "StartPage/StartPage.hpp"

#include  <chrono>
#include  <cmath>

namespace GameEngine
{
  class Client
  {
  public:
    Client(const std::string &ip, sf::VideoMode &videoMode);

    void  init(void);
    void  run(void);

    void  update(void);
    void  handleEvents(void);
    void  render(float alpha);

    void  exitGame(const std::string &);

  private:
    EventManager::Manager _eventManager;
    ResourcesManager  _resourcesManager;
    ECS::Manager      _ecsManager;
    GUI::Manager      _guiManager;
    // SceneManager   _sceneManager;
    // LibraryLoader _libraryLoader;
    // Network _network;

  private:
    sf::RenderWindow _window;

    std::string _ip;

    double  _gameEngineTick;
    double  _maxFrameRate;
    bool    _running;
  };
}
