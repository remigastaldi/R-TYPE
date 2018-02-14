#include "UpAndDownMove.hpp"

UpAndDownMove::UpAndDownMove(GameEngine::GameManagers &gameManagers, ECS::Entity entity) :
  IMove(gameManagers, entity),
  _gameManagers(gameManagers),
  _ecs(gameManagers.ecs),
  _event(gameManagers.event),
  _loader(gameManagers.libLoader),
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
