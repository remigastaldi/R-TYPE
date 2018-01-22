/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-20T20:45:23+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-22T01:46:03+01:00
 */


#include  "Ship.hpp"
#include <iostream>

Ship::Ship(GameEngine::GameManagers &gameManagers)
  : _gameManagers(gameManagers),
    _entity(_gameManagers.ecs.createEntity()),
    _fireTickCounter(0),
    _fire(false)
  {
    _gameManagers.resources.load<Sprite>("playersSpaceship", "../../Client/media/img/playerLobby/playersSpaceships.png");
    sf::Sprite &sprite = _gameManagers.resources.getContent<Sprite>("playersSpaceship");
    sprite.setRotation(90);
    sprite.setTextureRect(sf::IntRect(0, 0, 160, 160));
    sprite.setScale(0.6, 0.6);

    _gameManagers.ecs.addComponent<ECS::Components::Position>(_entity, ECS::Components::Position(200, 10));
    _gameManagers.ecs.addComponent<ECS::Components::Drawable>(_entity, ECS::Components::Drawable("playersSpaceship"));
    _gameManagers.ecs.addComponent<ECS::Components::Direction>(_entity, ECS::Components::Direction(0, 0, 7));

    _gameManagers.ecs.updateEntityToSystems(_entity);

    _gameManagers.event.addEvent<void, const std::string &>("SpaceKeyEvent");

    _gameManagers.event.listen<void, sf::Event>("KeyPressedEvent", [&](sf::Event event) { this->keyPressed(event);});
    _gameManagers.event.listen<void, sf::Event>("KeyReleasedEvent", [&](sf::Event event) { this->keyRelease(event);});
    _gameManagers.event.listen<void, const std::string &>("SpaceKeyEvent", [&](const std::string & msg) { this->fire(msg);});

    _gameManagers.sound.loadSound("shoot", "../../Client/media/sounds/shoot.wav");
    _gameManagers.sound.registerSoundWithEvent<void, sf::Event>("shoot", "SpaceKeyEvent");
  }

void  Ship::keyPressed(sf::Event event)
{
  std::shared_ptr<ECS::Components::Direction> direction = _gameManagers.ecs.getComponent<ECS::Components::Direction>(_entity);

  switch (event.key.code)
  {
  case sf::Keyboard::Key::Up :
    direction->yDirection = -1;
    break;
  case sf::Keyboard::Key::Down :
    direction->yDirection = 1;
    break;
  case sf::Keyboard::Key::Right :
    direction->xDirection = 1;
    break;
  case sf::Keyboard::Key::Left :
    direction->xDirection = -1;
    break;
  case sf::Keyboard::Key::Space :
    _fire = true;
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


void  Ship::keyRelease(sf::Event event)
{
  std::shared_ptr<ECS::Components::Direction> direction = _gameManagers.ecs.getComponent<ECS::Components::Direction>(_entity);

  switch (event.key.code)
  {
  case sf::Keyboard::Key::Up :
    direction->yDirection = 0;
    break;
  case sf::Keyboard::Key::Down :
    direction->yDirection = 0;
    break;
  case sf::Keyboard::Key::Right :
    direction->xDirection = 0;
    break;
  case sf::Keyboard::Key::Left :
    direction->xDirection = 0;
    break;
  case sf::Keyboard::Key::Space :
    _fire = false;
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

void  Ship::fire(const std::string &msg)
{
  (void) msg;

  ECS::Entity e = _gameManagers.ecs.createEntity();

  std::shared_ptr<ECS::Components::Position> position = _gameManagers.ecs.getComponent<ECS::Components::Position>(_entity);

  _gameManagers.ecs.addComponent<ECS::Components::Position>(e, ECS::Components::Position(
    static_cast<size_t>(position->x + 100), static_cast<size_t>(position->y)));
  _gameManagers.ecs.addComponent<ECS::Components::Drawable>(e, ECS::Components::Drawable("playersSpaceship"));
  _gameManagers.ecs.addComponent<ECS::Components::Direction>(e, ECS::Components::Direction(1, 0, 30));
  _gameManagers.ecs.updateEntityToSystems(e);
}


void  Ship::update(void)
{
  if (_fire && _fireTickCounter == 0)
  {
    _fireTickCounter++;
    _gameManagers.event.fire<void, const std::string &>("SpaceKeyEvent", "Fire");
  }
  else if (_fire && _fireTickCounter > 5)
    _fireTickCounter = 0;
  else if (_fire)
    _fireTickCounter++;
  else
    _fireTickCounter = 0;
}
