/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-22T10:35:17+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-24T20:00:54+01:00
 */

//COMMENT FAIRE BOUGER UN ENNEMI ?
//EASY AS FUCK !
//FAITES JUSTE:
//_managers.event.fire<void, std::string>("multiplayer go up", "ID");
//Listes des event utilisables:
//multiplayer go up
//  multiplayer go down
//multiplayer go left
//  multiplayer go right
//multiplayer shoot
//multiplayer join
//multiplayer disconnect
//multiplayer setPlayerName

#include <GameManagers.hpp>
#include "NetworkManager.hpp"

NetworkManager::NetworkManager(GameEngine::GameManagers &manager) :
_network(std::stol(manager.config.getKey("port")), 8000),
_managers(manager),
_mutex(),
_queue(),
_token()
{}

NetworkManager::~NetworkManager()
{}

void NetworkManager::init()
{
	_managers.event.listen<int, sf::Event>("KeyPressedEvent", [&](sf::Event event) -> int {this->keyPressed(event); return 0; });
  _managers.event.listen<int>("readyToPlayEvent", [&]() -> int {this->playerReady(); return 0; });
  _managers.event.listen<int>("PlayGameEvent", [&]() -> int {this->playGame(); return 0; });
  _managers.event.listen<int, sf::Event>("KeyReleasedEvent", [&](sf::Event event){this->keyRelease(event); return 0;});

	std::thread([&](){this->login();}).detach();

  std::thread([&](){this->mainLoop();}).detach();

	std::thread([&](){this->pingLoop();}).detach();
}

void NetworkManager::login()
{
  for (;;)
  {
		_mutex.lock();
    if (_token.empty()) {
			UDPPacket packet;
			packet.setCommand(RFC::Commands::LOGIN);
			packet.setData("usr", "root");
			packet.setData("pwd", "root");

			_network.send(packet, _managers.config.getKey("ip"));
			std::cout << "Trying to reconnect in 2 secondes..." << std::endl;
		} else {
			_mutex.unlock();
			return;
		}
		_mutex.unlock();
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));

  }
}

void NetworkManager::pingLoop()
{
  for (;;)
  {

		std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    UDPPacket packet;
    packet.setCommand(RFC::Commands::PING);
    packet.setToken(_token);

    _network.send(packet);
  }
}

void NetworkManager::mainLoop()
{
  for (;;)
  {
    UDPPacket packet = _network.receive();

    if (packet.getCommand() == RFC::Commands::LOGIN && packet.getResult() == RFC::Responses::SUCCESS) {
      _token = packet.getData("token");
    } else if (_token.empty()) {
			std::cout << "no token" << std::endl;
    } else {
			_mutex.lock();
			_queue.emplace_back(packet);
			_mutex.unlock();
		}
  }
}

void NetworkManager::update()
{
  UDPPacket packet;

  packet.setToken(_token);
	_mutex.lock();
	auto it = _queue.cbegin();
  while (it != _queue.cend())
  {

    // std::cout << "Command: " << std::to_string(static_cast<unsigned int>(it->getCommand())) << std::endl;
    // std::cout << "Result: " << std::to_string(static_cast<unsigned int>(it->getResult())) << std::endl;
    switch (it->getCommand()) {
      case RFC::Commands::CREATE_ROOM:
        packet.setCommand(RFC::Commands::JOIN_ROOM);
        packet.setData("roomId", "room1");
        std::cout << "CREATED ROOM" << std::endl;

        _network.send(packet);
        break;
      case RFC::Commands::JOIN_ROOM:
        if (it->getResult() == RFC::Responses::SUCCESS) {
          std::cout << "JOIN ROOM" << it->getData("name") << std::endl;
					_managers.event.fire<int, std::string const &>("changeScene", "LobbyPlayer");
					if (it->getData("player1") != "") {
						if ("player1" != it->getData("name")) {
							_managers.event.fire<int, std::string>("multiplayer join", it->getData("player1_token"));
						}
						_managers.event.fire<int, std::string, int>("PlayerJoinEvent", "player1", 1);
					}
					if (it->getData("player2") != "") {
						if ("player2" != it->getData("name")) {
							_managers.event.fire<int, std::string>("multiplayer join", it->getData("player2_token"));
						}

						_managers.event.fire<int, std::string, int>("PlayerJoinEvent", "player2", 2);
					}
					if (it->getData("player3") != "") {
						if ("player3" != it->getData("name")) {
							_managers.event.fire<int, std::string>("multiplayer join", it->getData("player3_token"));
						}
						_managers.event.fire<int, std::string, int>("PlayerJoinEvent", "player3", 3);
					}
					if (it->getData("player4") != "") {
						if ("player4" != it->getData("name")) {
							_managers.event.fire<int, std::string>("multiplayer join", it->getData("player4_token"));
						}
						_managers.event.fire<int, std::string, int>("PlayerJoinEvent", "player4", 4);
					}
        } else if (it->getResult() == RFC::Responses::PLAYER_JOIN) {
					int player = 0;
          std::cout << "PLAYER JOIN" << it->getData("name") << std::endl;
					if (it->getData("name") == "player1") {
						player = 1;
					} else if (it->getData("name") == "player2") {
						player = 2;
					} else if (it->getData("name") == "player3") {
						player = 3;
					} else if (it->getData("name") == "player4") {
						player = 4;
					}
          _managers.event.fire<int, std::string, int>("PlayerJoinEvent", it->getData("name"), player);
          _managers.event.fire<int, std::string>("multiplayer join", it->getData("token"));
        } else {
          std::cout << "JOIN ERROR" << std::endl;
        }
        break;
			case RFC::Commands::LEAVE_ROOM:
				std::cout << "LEAVE ROOM =====================" << std::endl;
      	_managers.event.fire<int, std::string>("PlayerLeaveEvent", it->getData("name"));
        break;
      case RFC::Commands::READY:
        if (it->getResult() == RFC::Responses::PLAYER_READY) {
          std::cout << "PLAYER " << it->getData("name") << " READY" << std::endl;
        } else {
          std::cout << "PLAYER NOT READY" << std::endl;
        }
        break;
      case RFC::Commands::KEY_PRESSED:
        std::cout << "KEY PRESSED " << it->getData("key") << std::endl;
        switch (std::stoi(it->getData("key"))) {
          case sf::Keyboard::Up:
            _managers.event.fire<int, std::string>("multiplayer go up", it->getData("token"));
            break;
          case sf::Keyboard::Down:
            _managers.event.fire<int, std::string>("multiplayer go down", it->getData("token"));
            break;
          case sf::Keyboard::Left:
            _managers.event.fire<int, std::string>("multiplayer go left", it->getData("token"));
            break;
          case sf::Keyboard::Right:
            _managers.event.fire<int, std::string>("multiplayer go right", it->getData("token"));
            break;
          case sf::Keyboard::Space:
            _managers.event.fire<int, std::string>("multiplayer shoot", it->getData("token"));
            break;
        }
        break;
			case RFC::Commands::KEY_RELEASE:
        std::cout << "KEY RELEASE " << it->getData("key") << std::endl;
        switch (std::stoi(it->getData("key"))) {
          case sf::Keyboard::Up:
            _managers.event.fire<int, std::string>("multiplayer release up", it->getData("token"));
            break;
          case sf::Keyboard::Down:
            _managers.event.fire<int, std::string>("multiplayer release down", it->getData("token"));
            break;
          case sf::Keyboard::Left:
            _managers.event.fire<int, std::string>("multiplayer release left", it->getData("token"));
            break;
          case sf::Keyboard::Right:
            _managers.event.fire<int, std::string>("multiplayer release right", it->getData("token"));
            break;
        }
        break;
      case RFC::Commands::START_GAME:
        std::cout << "GAME STARTED" << std::endl;
				_managers.event.fire<int, std::string>("changeScene", "IngameHUD");
				_managers.event.fire<int>("multiplayer game start");
        break;
      default:
          std::cout << "Unkown command " << std::to_string(static_cast<unsigned int>(it->getCommand())) << std::endl;
          std::cout << "Unkown response " << std::to_string(static_cast<unsigned int>(it->getResult())) << std::endl;
        break;
      case RFC::Commands::PING:break;
      case RFC::Commands::LOGIN:break;
      case RFC::Commands::GET_FRIENDS:break;
      case RFC::Commands::GET_PROFIL:break;
      case RFC::Commands::GET_SHIP_INFO:break;
      case RFC::Commands::BUY_SHIP_COMPONENT:break;
      case RFC::Commands::SEARCH_ROOM:break;
      case RFC::Commands::GET_ROOM_INFO:break;
      case RFC::Commands::NOT_READY:break;
      case RFC::Commands::SELECT_ROOM_LEVEL:break;
      case RFC::Commands::UNKNOWN:break;
    }

    it = _queue.erase(_queue.begin());
		if (it != _queue.cend())
			it = std::next(it);
  }
	_mutex.unlock();

}

void NetworkManager::playGame()
{
  UDPPacket packet;
  packet.setCommand(RFC::Commands::CREATE_ROOM);
  packet.setToken(_token);
  packet.setData("roomId", "room1");

  _network.send(packet);
}

void NetworkManager::playerReady()
{
  UDPPacket packet;
  packet.setCommand(RFC::Commands::READY);
  packet.setToken(_token);

  _network.send(packet);
}

void NetworkManager::keyPressed(sf::Event event)
{
  UDPPacket packet;

  switch (event.key.code)
  {
    case sf::Keyboard::Key::Up:
    case sf::Keyboard::Key::Down:
    case sf::Keyboard::Key::Right:
    case sf::Keyboard::Key::Left:
    case sf::Keyboard::Key::Space:
      packet.setCommand(RFC::Commands::KEY_PRESSED);
      packet.setToken(_token);
      packet.setData("key", std::to_string(static_cast<unsigned int>(event.key.code)));

      _network.send(packet);
			break;
    default :
			break;
  }
}

void NetworkManager::keyRelease(sf::Event event)
{
  UDPPacket packet;

  switch (event.key.code)
  {
    case sf::Keyboard::Key::Up:
    case sf::Keyboard::Key::Down:
    case sf::Keyboard::Key::Right:
    case sf::Keyboard::Key::Left:
    case sf::Keyboard::Key::Space:
      packet.setCommand(RFC::Commands::KEY_RELEASE);
      packet.setToken(_token);
      packet.setData("key", std::to_string(static_cast<unsigned int>(event.key.code)));

      _network.send(packet);
      break;
    default :
      break;
  }
}
