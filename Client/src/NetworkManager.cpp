#include "NetworkManager.hpp"


NetworkManager::NetworkManager(EventManager::Manager &eventManager) :
_network(4242, 8000),
_eventManager(eventManager)
{}

NetworkManager::~NetworkManager()
{}

void NetworkManager::init()
{
  _eventManager.listen<void, sf::Event>("KeyPressedEvent", [&](sf::Event event){this->keyPressed(event);});

  std::unordered_map<std::string, std::string>	map;
  map["cmd"] = RFC::Commands::LOGIN;
  map["usr"] = "root";
  map["pwd"] = "root";

  _network.send(map, "127.0.0.1");
}


void NetworkManager::keyPressed(sf::Event event)
{
  std::unordered_map<std::string, std::string>	map;

  switch (event.key.code)
  {
    case sf::Keyboard::Key::Up:
    case sf::Keyboard::Key::Down:
    case sf::Keyboard::Key::Right:
    case sf::Keyboard::Key::Left:
    case sf::Keyboard::Key::Space:
      map["cmd"] = RFC::Commands::KEY_PRESSED;
      map["key"] = std::to_string(event.key.code);
      _network.send(map);
      break;
    default :
      break;
  }


}
