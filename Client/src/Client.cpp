/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-17T04:07:04+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-21T03:08:06+01:00
 */


#include  "Client.hpp"

namespace GameEngine
{
  Client::Client(const std::string &ip, sf::VideoMode &videoMode)
    : _eventManager(),
    _resourcesManager(),
    _ecsManager(),
    _guiManager(_window),
    _window(videoMode, "R-Type", sf::Style::Titlebar | sf::Style::Resize),
    _ip(ip),
    _gameEngineTick(40),
    _maxFrameRate(60),
    _running(true)
  {}

  void  Client::init(void)
  {
    // load connection scene
    _ecsManager.createStoreFor(ECS::Components::Position::Type);
    _ecsManager.createStoreFor(ECS::Components::Drawable::Type);
    _ecsManager.createStoreFor(ECS::Components::Direction::Type);
    _ecsManager.addSystem<ECS::Systems::Mouvement>(_ecsManager);
    _ecsManager.addSystem<ECS::Systems::Render>(_resourcesManager, _ecsManager, _window);
    _ecsManager.initSystems();

    // Create events
    _eventManager.addEvent<void, const std::string &>("PlayGameEvent");
    _eventManager.addEvent<void, const std::string &>("ExitGameEvent");
    _eventManager.addEvent<void, const std::string &>("OptionsEvent");

    _eventManager.listen<void, const std::string &>("PlayGameEvent", std::bind(&Client::playGame, this, std::placeholders::_1));
    _eventManager.listen<void, const std::string &>("ExitGameEvent", std::bind(&Client::exitGame, this, std::placeholders::_1));

    _eventManager.addEvent<void, const std::string &>("ARROW_UP");
    _eventManager.addEvent<void, const std::string &>("ARROW_DOWN");
    _eventManager.addEvent<void, const std::string &>("ARROW_RIGHT");
    _eventManager.addEvent<void, const std::string &>("ARROW_LEFT");
  }

  void  Client::playGame(const std::string &message)
  {
    std::cout << message << std::endl;
  }

  void  Client::exitGame(const std::string &message)
  {
    std::cout << message << std::endl;
    _running = false;
  }
  void  Client::run(void)
  {
	  // StartPage	startPageScene(_resourcesManager, _guiManager, _eventManager);
    //
	  // startPageScene.onEnter();

    // LobbyPlayer lobbyPlayerScene(_resourcesManager,_guiManager, _eventManager);
    //
	  // lobbyPlayerScene.onEnter();
    _ship = std::make_shared<Ship>(_resourcesManager, _eventManager, _ecsManager);

    double nextGameTick = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();

    auto t1 = std::chrono::high_resolution_clock::now();
    while(_running)
    {
      double skipTick = 1000 / _gameEngineTick;
      int maxFrameSkip = sqrt(_gameEngineTick);

      int loops = 0;
      auto t2 = std::chrono::high_resolution_clock::now();
      handleEvents();
      while(std::chrono::duration_cast<std::chrono::milliseconds>(t2.time_since_epoch()).count() > nextGameTick
        && loops < maxFrameSkip)
      {
        update();
        nextGameTick += skipTick;
        loops++;
      }
      if (std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() >= (1000 / _maxFrameRate))
      {
        float interpolation = static_cast<float>((std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count()
          + skipTick - nextGameTick) /  skipTick);
        render(interpolation);
        t1 = std::chrono::high_resolution_clock::now();
      }
    }
  }

  void  Client::handleEvents(void)
  {
    sf::Event event;
    while (_window.pollEvent(event))
    {
      // if (event.type == sf::Event::Closed)
      //   _window.close();
    }
  }

  void  Client::update(void)
  {
    _ecsManager.updateSystemsRange(0.f, 0, 1);
  }

  void  Client::render(float alpha)
  {
    _window.clear();
    _guiManager.update(alpha);
    _ecsManager.updateSystemsRange(0.f, 1, 2);
    _window.display();
  }
}
