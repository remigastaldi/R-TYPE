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
  attack();
}

BasicAttack::~BasicAttack()
{
}

void BasicAttack::update()
{
  //TODO maybe something
}

ECS::Entity BasicAttack::getID()
{
  return _entity;
}

void BasicAttack::attack()
{
  ECS::Entity e = _ecs.createEntity();
  _attacks.push_back(e);

  _ecs.addComponent<ECS::Components::Position>(e, *_ecs.getComponent<ECS::Components::Position>(_ownerEntity).get());
  _ecs.addComponent<ECS::Components::Direction>(e, *_ecs.getComponent<ECS::Components::Direction>(_ownerEntity).get());
  _ecs.addComponent<ECS::Components::Drawable>(e, ECS::Components::Drawable("ennemy1"));
}

void BasicAttack::move()
{
  (*_move)->update();
}

void BasicAttack::playerHit(ECS::Entity entity)
{
  _ecs.getComponent<ECS::Components::Stats>(entity).get()->health -= _baseDamage;
}
