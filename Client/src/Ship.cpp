/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-20T20:45:23+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-21T04:23:43+01:00
 */


#include  "Ship.hpp"
#include <iostream>
Ship::Ship(ResourcesManager &resourceManager, EventManager::Manager &eventManager, ECS::Manager &ecsManager)
  : _resourcesManager(resourceManager),
    _eventManager(eventManager),
    _ecsManager(ecsManager)
  {
    _entity = _ecsManager.createEntity();

    _resourcesManager.load<Sprite>("../../Client/media/img/playerLobby/playersSpaceships.png");
    sf::Sprite &sprite = _resourcesManager.getContent<Sprite>("../../Client/media/img/playerLobby/playersSpaceships.png");
    sprite.setTextureRect(sf::IntRect(0, 0, 160, 160));

    _ecsManager.addComponent<ECS::Components::Position>(_entity, ECS::Components::Position(0, 10));
    _ecsManager.addComponent<ECS::Components::Drawable>(_entity, ECS::Components::Drawable("../../Client/media/img/playerLobby/playersSpaceships.png"));
    _ecsManager.addComponent<ECS::Components::Direction>(_entity, ECS::Components::Direction(0, 0, 10));

    _ecsManager.updateEntityToSystems(_entity);
    // _eventManager.listen<void, sf::Event>("KeyPressedEvent", [&](sf::Event event) { this->KeyPressed(event);});
    _eventManager.listen<void, sf::Event>("KeyPressedEvent", std::bind(&Ship::KeyPressed, this, std::placeholders::_1));
    _eventManager.listen<void, sf::Event>("KeyReleasedEvent", std::bind(&Ship::KeyRelease, this, std::placeholders::_1));
  }

void  Ship::KeyPressed(sf::Event event)
{
  std::shared_ptr<ECS::Components::Direction> direction = _ecsManager.getComponent<ECS::Components::Direction>(_entity);

  switch (event.key.code)
  {
  case sf::Keyboard::Key::Up :
    direction->yDirection = -1;
    std::cout << "UP" << std::endl;
    break;
  case sf::Keyboard::Key::Down :
    direction->yDirection = 1;
    std::cout << "Down" << std::endl;
    break;
  case sf::Keyboard::Key::Right :
    direction->xDirection = 1;
    std::cout << "Right" << std::endl;
    break;
  case sf::Keyboard::Key::Left :
    direction->xDirection = -1;
    std::cout << "Left" << std::endl;
    break;
  default :
    break;
  }
}


void  Ship::KeyRelease(sf::Event event)
{
  std::shared_ptr<ECS::Components::Direction> direction = _ecsManager.getComponent<ECS::Components::Direction>(_entity);

  switch (event.key.code)
  {
  case sf::Keyboard::Key::Up :
    direction->yDirection = 0;
    std::cout << "UP" << std::endl;
    break;
  case sf::Keyboard::Key::Down :
    direction->yDirection = 0;
    std::cout << "Down" << std::endl;
    break;
  case sf::Keyboard::Key::Right :
    direction->xDirection = 0;
    std::cout << "Right" << std::endl;
    break;
  case sf::Keyboard::Key::Left :
    direction->xDirection = 0;
    std::cout << "Left" << std::endl;
    break;
  default :
    break;
  }
}
