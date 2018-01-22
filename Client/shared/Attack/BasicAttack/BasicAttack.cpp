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
  _ecs.addComponent<ECS::Components::Collisionable>(_entity, ECS::Components::Collisionable(_entity));
  _ecs.addComponent<ECS::Components::Drawable>(_entity, ECS::Components::Drawable(_TEXTURE));
  _ecs.addComponent<ECS::Components::Position>(_entity, *_ecs.getComponent<ECS::Components::Position>(_ownerEntity).get());

  _ecs.updateEntityToSystems(_entity);

  std::shared_ptr<IMove> tmp;
  tmp.reset(_loader.move.get(_MOVE)(_ecs, _event, _loader, _entity));
  _move = tmp;
}

BasicAttack::~BasicAttack()
{
  LOG_SUCCESS << "Basic attack se detruit" << std::endl;
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
