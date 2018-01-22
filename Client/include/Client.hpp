/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-17T04:02:41+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-22T02:41:57+01:00
 */

#pragma once

#include  "config.hpp"

#include  "GameManagers.hpp"

#include  "GUIManager.hpp"
#include  "Logger/Logger.hpp"
#include  "EventManager.hpp"
#include  "ECS/Components/Components.hpp"
#include  "ECS/Systems/ClientSystems.hpp"
#include  "ECS/Systems/Collision.hpp"
#include  "NetworkManager.hpp"

#include  "StartPage/StartPage.hpp"
#include  "IngameHUD/IngameHUD.hpp"
#include  "Parallax/Parallax.hpp"

#include "Ship.hpp"

#include  <chrono>
#include  <cmath>
#include <DynamicLibrary/LibLoader.hpp>

namespace GameEngine
{
  class Client
  {
    public:
      Client(const std::string &ip, sf::VideoMode &videoMode);

      void init(void);
      void run(void);

      void update(void);
      void handleEvents(void);
      void render(float alpha);

      void playGame(const std::string &);
      void exitGame(const std::string &);

    private:
		Parallax _parallax;
      EventManager::Manager _eventManager;
      ResourcesManager _resourcesManager;
      ECS::Manager _ecsManager;
      GUI::Manager _guiManager;
      SoundManager _soundManager;
      GameEngine::GameManagers _gameManagers;
      // SceneManager   _sceneManager;
       LibLoader _libraryLoader;
      // Network _network;
      NetworkManager          _networkManager;

      std::shared_ptr<Ship> _ship;

      sf::RenderWindow _window;

      std::string _ip;

      double _gameEngineTick;
      double _maxFrameRate;
      bool _running;

      IMap *_myMap;
  };
}
