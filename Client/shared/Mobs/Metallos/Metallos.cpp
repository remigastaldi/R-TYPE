/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-22T10:02:46+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-20T22:43:03+01:00
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


  std::shared_ptr<Texture> texture = _gameManagers.resources.get<Texture>("metallos_texture");
  _spriteName = "metallos_sprite[" + std::to_string(_me) + "]";
  Sprite sprite(_spriteName, *texture);

  // sf::Sprite &spriteMetallos = _gameManagers.resources.getContent<Sprite>(_spriteName);
  sprite.getContent().setRotation(-90);
  sprite.getContent().setScale(0.8, 0.8);
  _gameManagers.resources.addResource<Sprite>(_spriteName, sprite);

  _ecs.addComponent<ECS::Components::Position>(_me, pos);
  _ecs.addComponent<ECS::Components::Drawable>(_me, ECS::Components::Drawable(_spriteName));
  _ecs.addComponent<ECS::Components::Collisionable>(_me, ECS::Components::Collisionable(_me, ECS::Components::Collisionable::Type::ENEMY_MISSILE));
  _ecs.addComponent<ECS::Components::Health>(_me, ECS::Components::Health(2));
  _ecs.addComponent<ECS::Components::Ennemy>(_me, ECS::Components::Ennemy());

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

void Metallos::unitOutOfSpace(ECS::Entity entity)
{
  (void) entity;
//  _attacks.erase(entity);
}
