/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-20T20:45:23+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-21T22:40:39+01:00
 */


#include  "Ship.hpp"
#include <iostream>

Ship::Ship(GameEngine::GameManagers &gameManager)
  : _gameManagers(gameManager),
    _entity(_gameManagers.ecs.createEntity()),
    _fireTickCounter(0),
    _fire(false)
  {
    _gameManagers.resources.load<Sprite>("playersSpaceship", "../../Client/media/img/playerLobby/playersSpaceships.png");
    sf::Sprite &sprite = _gameManagers.resources.getContent<Sprite>("playersSpaceship");
    sprite.setRotation(90);
    sprite.setTextureRect(sf::IntRect(0, 0, 160, 160));

    _gameManagers.ecs.addComponent<ECS::Components::Position>(_entity, ECS::Components::Position(200, 10));
    _gameManagers.ecs.addComponent<ECS::Components::Drawable>(_entity, ECS::Components::Drawable("playersSpaceship"));
    _gameManagers.ecs.addComponent<ECS::Components::Direction>(_entity, ECS::Components::Direction(0, 0, 10));

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
  }
}

void  Ship::fire(const std::string &msg)
{
  (void) msg;
  ECS::Entity e = _gameManagers.ecs.createEntity();

  std::shared_ptr<ECS::Components::Position> position = _gameManagers.ecs.getComponent<ECS::Components::Position>(_entity);

  _gameManagers.ecs.addComponent<ECS::Components::Position>(e, ECS::Components::Position(position->x + 100, position->y));
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
