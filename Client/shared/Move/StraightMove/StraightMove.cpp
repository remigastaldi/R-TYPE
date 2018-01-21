#include "StraightMove.hpp"

StraightMove::StraightMove(ECS::Manager &ecs, EventManager::Manager &event, LibLoader &loader, ECS::Entity entity) :
  IMove(ecs, event, loader, entity),
  _ecs(ecs),
  _event(event),
  _loader(_loader),
  _owner(entity)
{
  _ecs.addComponent<ECS::Components::Direction>(_owner, ECS::Components::Direction(-1, 0, 20));
}

StraightMove::~StraightMove() = default;

void StraightMove::update()
{
  //go straight so nothing to do
}