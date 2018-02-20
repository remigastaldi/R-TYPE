/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-22T10:02:46+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-20T18:57:15+01:00
 */


#include "BasicAttack.hpp"

BasicAttack::BasicAttack(GameEngine::GameManagers &gameManagers, MapEngine &mapEngine, ECS::Entity owner) :
  IAttack(gameManagers, mapEngine, owner),
  _gameManagers(gameManagers),
  _ecs(gameManagers.ecs),
  _event(gameManagers.event),
  _loader(gameManagers.libLoader),
  _mapEngine(mapEngine),
  _ownerEntity(owner),
  _entity(gameManagers.ecs.createEntity()),
  _attacks(),
  _move(),
  _spriteName()
{
  Logger::get().setOutput(CONSOLE_LOG);

  std::shared_ptr<Texture> texture = _gameManagers.resources.get<Texture>("basick_attack_texture");
  _spriteName = "basic_attack_sprite[" + std::to_string(_entity) + "]";

  Sprite sprite(_spriteName, *texture);
  _gameManagers.resources.addResource<Sprite>(_spriteName, sprite);

  sf::Sprite &spriteMissiles = _gameManagers.resources.getContent<Sprite>(_spriteName);
  spriteMissiles.setRotation(-90);

  _ecs.addComponent<ECS::Components::Collisionable>(_entity, ECS::Components::Collisionable(_entity, ECS::Components::Collisionable::Type::MISSILE));
  _ecs.addComponent<ECS::Components::Drawable>(_entity, ECS::Components::Drawable(_spriteName));
  ECS::Components::Position pos = *_ecs.getComponent<ECS::Components::Position>(_ownerEntity);
  pos.x -= 150;
  _ecs.addComponent<ECS::Components::Position>(_entity, pos);
 // _ecs.addComponent<ECS::Components::Stats>(_entity, ECS::Components::Stats(1));
  _ecs.addComponent<ECS::Components::Damages>(_entity, ECS::Components::Damages(1));

  _ecs.updateEntityToSystems(_entity);

  std::shared_ptr<IMove> tmp(_loader.move.get(_MOVE)(_gameManagers, _entity, -1, 5));
  _mapEngine.addObject(tmp->getID(), tmp);
}

BasicAttack::~BasicAttack()
{
  _gameManagers.resources.release(_spriteName);
  _ecs.destroyEntity(_entity);
}

void BasicAttack::update()
{
  //move();
}

ECS::Entity BasicAttack::getID() const
{
  return _entity;
}

void BasicAttack::move()
{
  _move->update();
}

void BasicAttack::playerHit(ECS::Entity entity)
{
  // if (_ecs.getComponent<ECS::Components::Stats>(entity).get() != nullptr)
  //   _ecs.getComponent<ECS::Components::Stats>(entity).get()->health -= _baseDamage;
}
