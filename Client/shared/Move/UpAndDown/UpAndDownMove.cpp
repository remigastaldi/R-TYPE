/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-02-15T15:02:13+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-19T18:15:43+01:00
 */


#include "UpAndDownMove.hpp"

UpAndDownMove::UpAndDownMove(GameEngine::GameManagers &gameManagers, ECS::Entity entity, int direction, int speed) :
  IMove(gameManagers, entity),
  _gameManagers(gameManagers),
  _ecs(gameManagers.ecs),
  _event(gameManagers.event),
  _loader(gameManagers.libLoader),
  _owner(entity)
{
  Logger::get().setOutput(CONSOLE_LOG);

  _ecs.addComponent<ECS::Components::Direction>(_owner, ECS::Components::Direction(direction, 1, speed));

  _ecs.updateEntityToSystems(_owner);
}

UpAndDownMove::~UpAndDownMove()
{
  _ecs.extractComponent<ECS::Components::Direction>(_owner);
  _ecs.updateEntityToSystems(_owner);
}

void UpAndDownMove::update()
{
  std::shared_ptr<ECS::Components::Position> pos = _ecs.getComponent<ECS::Components::Position>(_owner);

  std::shared_ptr<ECS::Components::Direction> dir = _ecs.getComponent<ECS::Components::Direction>(_owner);

  if (!pos)
    return;

  if (_isForwarding-- <= 0) {
    dir->xDirection = 0;
    _isForwarding = 40;
  }

  if (pos->y < 40) {
    dir->yDirection = 1;
    if (pos->x > 200) {
      dir->xDirection = -1;
      _isForwarding = 40;
    }
  }
  if (pos->y > 1050) {
    dir->yDirection = -1;
    if (pos->x > 200) {
      dir->xDirection = -1;
      _isForwarding = 40;
    }
  }
}

ECS::Entity UpAndDownMove::getID() const
{
  return (_owner);
}
