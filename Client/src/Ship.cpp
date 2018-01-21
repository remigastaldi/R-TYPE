/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-20T20:45:23+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-21T03:07:51+01:00
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
    _ecsManager.addComponent<ECS::Components::Direction>(_entity, ECS::Components::Direction(0));

    _ecsManager.updateEntityToSystems(_entity);
    _eventManager.listen<void, const std::string &>("ARROW_UP", std::bind(&Ship::go_Up, this, std::placeholders::_1));
    _eventManager.listen<void, const std::string &>("ARROW_DOWN", std::bind(&Ship::go_Down, this, std::placeholders::_1));
    _eventManager.listen<void, const std::string &>("ARROW_RIGHT", std::bind(&Ship::go_Right, this, std::placeholders::_1));
    _eventManager.listen<void, const std::string &>("ARROW_LEFT", std::bind(&Ship::go_Left, this, std::placeholders::_1));
  }

void  Ship::go_Up(const std::string &data)
{
  std::shared_ptr<ECS::Components::Direction> body = _ecsManager.getComponent<ECS::Components::Direction>(_entity);
  std::cout << "UP" << std::endl;
}

void  Ship::go_Down(const std::string &data)
{
  std::shared_ptr<ECS::Components::Direction> body = _ecsManager.getComponent<ECS::Components::Direction>(_entity);
  std::cout << "Down" << std::endl;

}

void  Ship::go_Right(const std::string &data)
{
  std::shared_ptr<ECS::Components::Direction> body = _ecsManager.getComponent<ECS::Components::Direction>(_entity);
  std::cout << "Right" << std::endl;

}

void  Ship::go_Left(const std::string &data)
{
  std::shared_ptr<ECS::Components::Direction> body = _ecsManager.getComponent<ECS::Components::Direction>(_entity);
  std::cout << "Left" << std::endl;

}
