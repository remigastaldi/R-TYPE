/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-22T10:02:46+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-22T10:25:04+01:00
 */


#include "BasicAttack.hpp"

BasicAttack::BasicAttack(GameEngine::GameManagers &gameManagers, ECS::Entity owner) :
  IAttack(gameManagers, owner),
  _gameManagers(gameManagers),
  _ecs(gameManagers.ecs),
  _event(gameManagers.event),
  _loader(gameManagers.libLoader),
  _ownerEntity(owner),
  _spriteName()
{
  Logger::get().setOutput(CONSOLE_LOG);

  _entity = _ecs.createEntity();

  std::shared_ptr<Texture> texture(_gameManagers.resources.get<Texture>("playersMissilesTexture"));
  _spriteName = "basic_attack_sprite[" + std::to_string(_entity) + "]";

  Sprite sprite(_spriteName, *texture);
  _gameManagers.resources.addResource<Sprite>(_spriteName, sprite);

  sf::Sprite &spriteMissiles = _gameManagers.resources.getContent<Sprite>(_spriteName);
  spriteMissiles.setRotation(-90);
  spriteMissiles.setTextureRect(sf::IntRect(0, 0, 30, 112));

  _ecs.addComponent<ECS::Components::Collisionable>(_entity, ECS::Components::Collisionable(_entity, ECS::Components::Collisionable::Type::ENNEMY));
  _ecs.addComponent<ECS::Components::Drawable>(_entity, ECS::Components::Drawable(_spriteName));
  ECS::Components::Position pos = *_ecs.getComponent<ECS::Components::Position>(_ownerEntity).get();
  pos.x -= 600;
  _ecs.addComponent<ECS::Components::Position>(_entity, pos);
  _ecs.addComponent<ECS::Components::Stats>(_entity, ECS::Components::Stats(1));

  _ecs.updateEntityToSystems(_entity);

  std::shared_ptr<IMove> tmp;
  tmp.reset(_loader.move.get(_MOVE)(_gameManagers, _entity));
  _move = tmp;
}

BasicAttack::~BasicAttack()
{
  _gameManagers.resources.release(_spriteName);
  _ecs.destroyEntity(_entity);
}

void BasicAttack::update()
{
  move();
}

ECS::Entity BasicAttack::getID()
{
  return _entity;
}

void BasicAttack::move()
{
  _move->update();
}

void BasicAttack::playerHit(ECS::Entity entity)
{
  if (_ecs.getComponent<ECS::Components::Stats>(entity).get() != nullptr)
    _ecs.getComponent<ECS::Components::Stats>(entity).get()->health -= _baseDamage;
}
