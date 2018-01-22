#include "UpAndDownMove.hpp"

UpAndDownMove::UpAndDownMove(ECS::Manager &ecs, EventManager::Manager &event, LibLoader &loader, ECS::Entity entity) :
  IMove(ecs, event, loader, entity),
  _ecs(ecs),
  _event(event),
  _loader(loader),
  _owner(entity)
{
  Logger::get().setOutput(CONSOLE_LOG);

  _ecs.addComponent<ECS::Components::Direction>(_owner, ECS::Components::Direction(0, 1, 2));

  _ecs.updateEntityToSystems(_owner);
}

UpAndDownMove::~UpAndDownMove()
{
}

void UpAndDownMove::update()
{
  auto pos = _ecs.getComponent<ECS::Components::Position>(_owner);

  if (pos->y < 40)
    _ecs.getComponent<ECS::Components::Direction>(_owner)->yDirection = 1;
  if (pos->y > 1000)
    _ecs.getComponent<ECS::Components::Direction>(_owner)->yDirection = -1;
}