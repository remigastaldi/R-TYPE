#include "UpAndDownMove.hpp"

UpAndDownMove::UpAndDownMove(ECS::Manager &ecs, EventManager::Manager &event, LibLoader &loader, ECS::Entity entity) :
  IMove(ecs, event, loader, entity),
  _ecs(ecs),
  _event(event),
  _loader(loader),
  _owner(entity)
{
  Logger::get().setOutput(CONSOLE_LOG);
//  _ecs.getComponent<ECS::Components::Direction>(_owner)->xDirection
}

UpAndDownMove::~UpAndDownMove()
{
}

void UpAndDownMove::update()
{
  _lastTickUpdate += 1;
  if (_lastTickUpdate >= _needTickToUpdate)
  {
    _lastTickUpdate = 0;

  }
}