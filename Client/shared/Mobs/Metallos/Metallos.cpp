/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-22T10:02:46+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-19T18:25:09+01:00
 */


#include "Metallos.hpp"

Metallos::Metallos(GameEngine::GameManagers &gameManagers, MapEngine &mapEngine, ECS::Components::Position pos) :
  IMob(gameManagers, mapEngine, pos),
  _me(gameManagers.ecs.createEntity()),
  _gameManagers(gameManagers),
  _ecs(gameManagers.ecs),
  _event(gameManagers.event),
  _loader(gameManagers.libLoader),
  _mapEngine(mapEngine),
  _spriteName()
{
  Logger::get().setOutput(CONSOLE_LOG);


  LOG_INFO << "Creating Metaloss" << std::endl;

  LOG_INFO << "Entity ID " << _me << std::endl;

  std::shared_ptr<Texture> texture = _gameManagers.resources.load<Texture>("metallos_texture", "../../Client/media/img/ship/enemies/CX16-X2.png");
  _spriteName = "metallos_sprite[" + std::to_string(_me) + "]";
  Sprite sprite(_spriteName, *texture);

  // sf::Sprite &spriteMetallos = _gameManagers.resources.getContent<Sprite>(_spriteName);
  sprite.getContent().setRotation(-90);
  sprite.getContent().setScale(0.8, 0.8);
  _gameManagers.resources.addResource<Sprite>(_spriteName, sprite);

  _ecs.addComponent<ECS::Components::Position>(_me, pos);
  _ecs.addComponent<ECS::Components::Drawable>(_me, ECS::Components::Drawable(_spriteName));
  _ecs.addComponent<ECS::Components::Collisionable>(_me, ECS::Components::Collisionable(_me, ECS::Components::Collisionable::Type::ENNEMY));
  _ecs.addComponent<ECS::Components::Stats>(_me, ECS::Components::Stats(1));

  _ecs.updateEntityToSystems(_me);

  std::shared_ptr<IMove> tmp(_loader.move.get(_MOVE_NAME)(_gameManagers, _me, 0, 2));
  _mapEngine.addObject<IMove>(tmp->getID(), tmp);
}

Metallos::~Metallos()
{
  _gameManagers.resources.release(_spriteName);
  _ecs.destroyEntity(_me);
}

int Metallos::getDifficulty() const
{
  return _difficulty;
}

void Metallos::update()
{
  _curTime -= 1;

  if (_curTime <= 0)
  {
    _curTime = _timeBetweenAttack;

    std::shared_ptr<IAttack> tmp(_loader.attack.get(_ATTACK_NAME)(_gameManagers, _mapEngine, _me));
    _mapEngine.addObject<IAttack>(tmp->getID(), tmp);
  }
}

ECS::Entity Metallos::getID() const
{
  return _me;
}

void Metallos::playerHit(ECS::Entity by, ECS::Entity to)
{
  (void) by;
  (void) to;
  // for (auto &it: _attacks)
  // {
  //   if (it.first == by)
  //     it.second->playerHit(to);
  //   if (it.first == to)
  //     it.second->playerHit(by);
  // }
}

void Metallos::unitOutOfSpace(ECS::Entity entity)
{
  (void) entity;
//  _attacks.erase(entity);
}
