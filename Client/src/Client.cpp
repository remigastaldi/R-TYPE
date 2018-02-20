/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-17T04:07:04+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-20T15:36:50+01:00
 */


#include <LibraryInterfaces/IMap.hpp>
#include <LobbyPlayer/LobbyPlayer.hpp>
#include <ECS/Components/Stats.hpp>
#include  "Client.hpp"

namespace GameEngine
{
  Client::Client(const std::string &ip, sf::VideoMode &videoMode)
    :
    _eventManager(),
    _resourcesManager(),
    _ecsManager(),
    _guiManager(_window),
    _soundManager(_resourcesManager, _eventManager),
    _libraryLoader(),
    _gameManagers(_resourcesManager, _eventManager, _ecsManager, _soundManager, _libraryLoader),
    _networkManager(_eventManager),
    _window(videoMode, "R-Type", sf::Style::Titlebar),
    _ip(ip),
    _gameEngineTick(120),
    _maxFrameRate(60),
    _running(true),
    _sceneManager(),
    _myMap(nullptr),
    _multiplayerManager(_ecsManager, _eventManager, _resourcesManager)
  {}

  void Client::init()
  {
    // load connection scene
    _ecsManager.createStoreFor<ECS::Components::Parallax>();
    _ecsManager.createStoreFor<ECS::Components::Position>();
    _ecsManager.createStoreFor<ECS::Components::Drawable>();
    _ecsManager.createStoreFor<ECS::Components::Direction>();
    _ecsManager.createStoreFor<ECS::Components::Collisionable>();
    _ecsManager.createStoreFor<ECS::Components::Player>();
    _ecsManager.createStoreFor<ECS::Components::Animated>();
    _ecsManager.createStoreFor<ECS::Components::Player>();
    _ecsManager.createStoreFor<ECS::Components::CollisionFrame>();

    _ecsManager.addSystem<ECS::Systems::Parallax>(_ecsManager, _resourcesManager);
    _ecsManager.addSystem<ECS::Systems::Mouvement>(_eventManager, _ecsManager);
    _ecsManager.addSystem<ECS::Systems::Collision>(_eventManager, _resourcesManager, _ecsManager);
    _ecsManager.addSystem<ECS::Systems::Animation>(_eventManager, _resourcesManager, _ecsManager);
    _ecsManager.addSystem<ECS::Systems::Render>(_resourcesManager, _ecsManager, _window);
    _ecsManager.addSystem<ECS::Systems::CleanupFrameCollisionComponents>(_ecsManager);
    _ecsManager.initSystems();

    // Create events
    _eventManager.addEvent<void, const std::string &>("PlayGameEvent");
    _eventManager.addEvent<void, const std::string &>("ExitGameEvent");
    _eventManager.addEvent<void, const std::string &>("OptionsEvent");

    _eventManager.listen<void, const std::string &>("PlayGameEvent",
                                                    std::bind(&Client::playGame, this, std::placeholders::_1));
    _eventManager.listen<void, const std::string &>("ExitGameEvent",
                                                    std::bind(&Client::exitGame, this, std::placeholders::_1));

    _eventManager.addEvent<void, sf::Event>("KeyPressedEvent");
    _eventManager.addEvent<void, sf::Event>("KeyReleasedEvent");

    //  _networkManager.init();
    //Loading library
    _libraryLoader.map.addFolder("../ressources/map/");
    _libraryLoader.mob.addFolder("../ressources/mob/");
    _libraryLoader.move.addFolder("../ressources/move/");
    _libraryLoader.attack.addFolder("../ressources/attack/");
    _libraryLoader.updateAll();

    //Escape key
    _eventManager.listen<void, sf::Event>("KeyPressedEvent", [&](sf::Event ev) -> void {
      if (ev.key.code == sf::Keyboard::Escape) {
        LOG_SUCCESS << "Exit" << std::endl;
        exit(0);
      }
    });

    //Scenes
    _sceneManager.addScene<StartPage>("StartPage", _resourcesManager, _guiManager, _eventManager);
    _sceneManager.addScene<LobbyPlayer>("LobbyPlayer", _resourcesManager, _guiManager, _eventManager);
    _sceneManager.addScene<IngameHUD>("IngameHUD", _resourcesManager, _guiManager, _eventManager);

    _eventManager.listen<void, std::string>("changeScene", [&](std::string scene) -> void {
      _sceneManager.pushScene(scene);
    });

    _eventManager.listen<void>("popScene", [&]() -> void {
      _sceneManager.popScene();
    });
  }

  void Client::playGame(const std::string &message)
  {
    std::cout << message << std::endl;
  }

  void Client::exitGame(const std::string &message)
  {
    std::cout << message << std::endl;
    _running = false;
  }

  void Client::run(void)
  {
    _sceneManager.pushScene("IngameHUD");

    _myMap.reset(_libraryLoader.map.get("KirbyMap")(_gameManagers));

    long int nextGameTick = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::high_resolution_clock::now().time_since_epoch()).count();

    auto t1 = std::chrono::high_resolution_clock::now();
    while (_running) {
      int skipTick = 1000 / _gameEngineTick;
      int maxFrameSkip = sqrt(_gameEngineTick);

      int loops = 0;
      handleEvents();
      while (std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::high_resolution_clock::now().time_since_epoch()).count() > nextGameTick
             && loops < maxFrameSkip) {
        update();
        nextGameTick += skipTick;
        loops++;
      }
      if (
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - t1).count() >=
        (1000 / _maxFrameRate)) {
        float interpolation = static_cast<float>((std::chrono::duration_cast<std::chrono::milliseconds>(
          std::chrono::high_resolution_clock::now().time_since_epoch()).count()
                                                  + skipTick - nextGameTick) / skipTick);
        render(interpolation);
        t1 = std::chrono::high_resolution_clock::now();
      }
    }
  }

  void Client::handleEvents(void)
  {
    sf::Event event;
    while (_window.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::KeyPressed :
          _eventManager.fire<void, sf::Event>("KeyPressedEvent", event);
          break;
        case sf::Event::KeyReleased :
          _eventManager.fire<void, sf::Event>("KeyReleasedEvent", event);
          break;
        case sf::Event::Closed:
          break;
        case sf::Event::Resized:
          break;
        case sf::Event::LostFocus:
          break;
        case sf::Event::GainedFocus:
          break;
        case sf::Event::TextEntered:
          break;
        case sf::Event::MouseWheelMoved:
          break;
        case sf::Event::MouseWheelScrolled:
          break;
        case sf::Event::MouseButtonPressed:
          break;
        case sf::Event::MouseButtonReleased:
          break;
        case sf::Event::MouseMoved:
          break;
        case sf::Event::MouseEntered:
          break;
        case sf::Event::MouseLeft:
          break;
        case sf::Event::JoystickButtonPressed:
          break;
        case sf::Event::JoystickButtonReleased:
          break;
        case sf::Event::JoystickMoved:
          break;
        case sf::Event::JoystickConnected:
          break;
        case sf::Event::JoystickDisconnected:
          break;
        case sf::Event::TouchBegan:
          break;
        case sf::Event::TouchMoved:
          break;
        case sf::Event::TouchEnded:
          break;
        case sf::Event::SensorChanged:
          break;
        case sf::Event::Count:
          break;
      }
    }
  }

  void Client::update(void)
  {
    //_networkManager.update();
    _myMap->update();
    _ecsManager.updateSystemsRange(0.f, 0, 5);
  }

  void Client::render(float alpha)
  {
//		std::cout << "entities: " << _ecsManager.getEntities().size() << std::endl;
    _window.clear();
    _ecsManager.updateSystemsRange(0.f, 5, 6);
    _guiManager.update(alpha);
    _window.display();
  }
}
