#include "StraightMove.hpp"

StraightMove::StraightMove(ECS::Manager &ecs, EventManager::Manager &event) :
  IMove(ecs, event),
  _ecs(ecs),
  _event(event)
{
  _entity = _ecs.createEntity();

  _ecs.addComponent<ECS::Components::Position>(_entity, *_ecs.getComponent<ECS::Components::Position>(_owner).get());
  _ecs.addComponent<ECS::Components::Direction>(_entity, *_ecs.getComponent<ECS::Components::Direction>(_owner).get());
  _ecs.addComponent<ECS::Components::Drawable>(_entity, ECS::Components::Drawable("ennemy1"));
}

StraightMove::~StraightMove() = default;

const std::string &StraightMove::getName() const
{
  return name;
}

void StraightMove::update(const float time)
{
  //go straight so nothing to do
}

ECS::Entity StraightMove::getID()
{
  return _entity;
}

void StraightMove::giveOwnerEntity(ECS::Entity entity)
{
  _owner  = entity;
}
