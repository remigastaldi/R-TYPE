#include "NetworkManager.hpp"

NetworkManager::NetworkManager(EventManager::Manager &eventManager) :
_network(4243, 8000),
_eventManager(eventManager),
_mutex(),
_queue(),
_mainLoop(),
_token()
{}

NetworkManager::~NetworkManager()
{}

void NetworkManager::init()
{
  _eventManager.listen<void, sf::Event>("KeyPressedEvent", [&](sf::Event event){this->keyPressed(event);});
  _eventManager.listen<void>("PlayGameEvent", [&](){this->playGame();});

  _mainLoop = std::make_shared<std::thread>([&](){this->mainLoop();});


  UDPPacket packet;
  packet.setCommand(RFC::Commands::LOGIN);
  packet.setData("usr", "root");
  packet.setData("pwd", "root");

  _network.send(packet, "127.0.0.1");
  //_eventManager.fire<void, const std::string &>("PlayerJoinEvent", "Slut");

}

void NetworkManager::mainLoop()
{
  for (;;)
  {
    UDPPacket packet = _network.receive();

    _mutex.lock();
    if (packet.getCommand() == RFC::Commands::LOGIN && packet.getResult() == RFC::Responses::SUCCESS) {
      _token = packet.getData("token");
    } else {
      _queue.emplace_back(packet);
    }
    _mutex.unlock();

  }
}

void NetworkManager::update()
{
  UDPPacket packet;

  packet.setToken(_token);
  for (auto & it : _queue)
  {
    _mutex.lock();
    switch (it.getCommand()) {
      case RFC::Commands::CREATE_ROOM:
        packet.setCommand(RFC::Commands::JOIN_ROOM);
        packet.setData("roomId", "room1");

        _network.send(packet);
        break;
      case RFC::Commands::JOIN_ROOM:
        if (it.getResult() == RFC::Responses::SUCCESS) {
          std::cout << "JOIN SUCCESS" << std::endl;
        } else {
          std::cout << "JOIN ERROR" << std::endl;
        }
        break;
      default:
          std::cout << "Unkown command " << std::to_string(static_cast<unsigned int>(it.getCommand())) << std::endl;
          std::cout << "Unkown response " << std::to_string(static_cast<unsigned int>(it.getResult())) << std::endl;
        break;
      case RFC::Commands::PING:break;
      case RFC::Commands::LOGIN:break;
      case RFC::Commands::GET_FRIENDS:break;
      case RFC::Commands::GET_PROFIL:break;
      case RFC::Commands::GET_SHIP_INFO:break;
      case RFC::Commands::BUY_SHIP_COMPONENT:break;
      case RFC::Commands::SEARCH_ROOM:break;
      case RFC::Commands::GET_ROOM_INFO:break;
      case RFC::Commands::LEAVE_ROOM:break;
      case RFC::Commands::READY:break;
      case RFC::Commands::NOT_READY:break;
      case RFC::Commands::START_GAME:break;
      case RFC::Commands::SELECT_ROOM_LEVEL:break;
      case RFC::Commands::KEY_PRESSED:break;
      case RFC::Commands::UNKNOWN:break;
    }

    _queue.erase(_queue.begin());
    _mutex.unlock();
  }
}

void NetworkManager::playGame()
{
  UDPPacket packet;
  packet.setCommand(RFC::Commands::CREATE_ROOM);
  packet.setToken(_token);
  packet.setData("roomId", "room1");

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
      case sf::Keyboard::Unknown:break;
      case sf::Keyboard::A:break;
      case sf::Keyboard::B:break;
      case sf::Keyboard::C:break;
      case sf::Keyboard::D:break;
      case sf::Keyboard::E:break;
      case sf::Keyboard::F:break;
      case sf::Keyboard::G:break;
      case sf::Keyboard::H:break;
      case sf::Keyboard::I:break;
      case sf::Keyboard::J:break;
      case sf::Keyboard::K:break;
      case sf::Keyboard::L:break;
      case sf::Keyboard::M:break;
      case sf::Keyboard::N:break;
      case sf::Keyboard::O:break;
      case sf::Keyboard::P:break;
      case sf::Keyboard::Q:break;
      case sf::Keyboard::R:break;
      case sf::Keyboard::S:break;
      case sf::Keyboard::T:break;
      case sf::Keyboard::U:break;
      case sf::Keyboard::V:break;
      case sf::Keyboard::W:break;
      case sf::Keyboard::X:break;
      case sf::Keyboard::Y:break;
      case sf::Keyboard::Z:break;
      case sf::Keyboard::Num0:break;
      case sf::Keyboard::Num1:break;
      case sf::Keyboard::Num2:break;
      case sf::Keyboard::Num3:break;
      case sf::Keyboard::Num4:break;
      case sf::Keyboard::Num5:break;
      case sf::Keyboard::Num6:break;
      case sf::Keyboard::Num7:break;
      case sf::Keyboard::Num8:break;
      case sf::Keyboard::Num9:break;
      case sf::Keyboard::Escape:break;
      case sf::Keyboard::LControl:break;
      case sf::Keyboard::LShift:break;
      case sf::Keyboard::LAlt:break;
      case sf::Keyboard::LSystem:break;
      case sf::Keyboard::RControl:break;
      case sf::Keyboard::RShift:break;
      case sf::Keyboard::RAlt:break;
      case sf::Keyboard::RSystem:break;
      case sf::Keyboard::Menu:break;
      case sf::Keyboard::LBracket:break;
      case sf::Keyboard::RBracket:break;
      case sf::Keyboard::SemiColon:break;
      case sf::Keyboard::Comma:break;
      case sf::Keyboard::Period:break;
      case sf::Keyboard::Quote:break;
      case sf::Keyboard::Slash:break;
      case sf::Keyboard::BackSlash:break;
      case sf::Keyboard::Tilde:break;
      case sf::Keyboard::Equal:break;
      case sf::Keyboard::Dash:break;
      case sf::Keyboard::Return:break;
      case sf::Keyboard::BackSpace:break;
      case sf::Keyboard::Tab:break;
      case sf::Keyboard::PageUp:break;
      case sf::Keyboard::PageDown:break;
      case sf::Keyboard::End:break;
      case sf::Keyboard::Home:break;
      case sf::Keyboard::Insert:break;
      case sf::Keyboard::Delete:break;
      case sf::Keyboard::Add:break;
      case sf::Keyboard::Subtract:break;
      case sf::Keyboard::Multiply:break;
      case sf::Keyboard::Divide:break;
      case sf::Keyboard::Numpad0:break;
      case sf::Keyboard::Numpad1:break;
      case sf::Keyboard::Numpad2:break;
      case sf::Keyboard::Numpad3:break;
      case sf::Keyboard::Numpad4:break;
      case sf::Keyboard::Numpad5:break;
      case sf::Keyboard::Numpad6:break;
      case sf::Keyboard::Numpad7:break;
      case sf::Keyboard::Numpad8:break;
      case sf::Keyboard::Numpad9:break;
      case sf::Keyboard::F1:break;
      case sf::Keyboard::F2:break;
      case sf::Keyboard::F3:break;
      case sf::Keyboard::F4:break;
      case sf::Keyboard::F5:break;
      case sf::Keyboard::F6:break;
      case sf::Keyboard::F7:break;
      case sf::Keyboard::F8:break;
      case sf::Keyboard::F9:break;
      case sf::Keyboard::F10:break;
      case sf::Keyboard::F11:break;
      case sf::Keyboard::F12:break;
      case sf::Keyboard::F13:break;
      case sf::Keyboard::F14:break;
      case sf::Keyboard::F15:break;
      case sf::Keyboard::Pause:break;
      case sf::Keyboard::KeyCount:break;
  }


}
