/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-22T10:02:46+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-22T10:25:04+01:00
 */


#include <ECS/Components/Components.hpp>
#include "BasicAttack.hpp"

BasicAttack::BasicAttack(ECS::Manager &ecs, EventManager::Manager &event, LibLoader &loader, ECS::Entity owner) :
  IAttack(ecs, event, loader, owner),
  _ecs(ecs),
  _event(event),
  _loader(loader),
  _ownerEntity(owner)
{
  Logger::get().setOutput(CONSOLE_LOG);

  _entity = _ecs.createEntity();
  _ecs.addComponent<ECS::Components::Collisionable>(_entity, ECS::Components::Collisionable(_entity, ECS::Components::Collisionable::Type::ENNEMY));
  _ecs.addComponent<ECS::Components::Drawable>(_entity, ECS::Components::Drawable(_TEXTURE));
  _ecs.addComponent<ECS::Components::Position>(_entity,
                                               *_ecs.getComponent<ECS::Components::Position>(_ownerEntity).get());

  _ecs.updateEntityToSystems(_entity);

  _move = std::make_unique<IMove *>(_loader.move.get(_MOVE)(_ecs, _event, _loader, _entity));
}

BasicAttack::~BasicAttack()
{
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
  (*_move)->update();
}

void BasicAttack::playerHit(ECS::Entity entity)
{
  if (_ecs.getComponent<ECS::Components::Stats>(entity).get() != nullptr)
    _ecs.getComponent<ECS::Components::Stats>(entity).get()->health -= _baseDamage;
}
