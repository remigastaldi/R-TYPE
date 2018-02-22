/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-02-15T15:02:13+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-19T18:17:54+01:00
 */

#include "SinusoideMove.hpp"

SinusoideMove::SinusoideMove(GameEngine::GameManagers &gameManagers, ECS::Entity entity, int direction, int speed) :
  IMove(gameManagers, entity),
  _gameManagers(gameManagers),
  _ecs(gameManagers.ecs),
  _event(gameManagers.event),
  _loader(gameManagers.libLoader),
  _owner(entity)
{
  Logger::get().setOutput(CONSOLE_LOG);

  _ecs.addComponent<ECS::Components::Direction>(_owner, ECS::Components::Direction(direction, -1, speed));

  _ecs.updateEntityToSystems(_owner);
}

SinusoideMove::~SinusoideMove()
{
  _ecs.extractComponent<ECS::Components::Direction>(_owner);
  _ecs.updateEntityToSystems(_owner);
}

void SinusoideMove::update()
{
  auto pos = _ecs.getComponent<ECS::Components::Position>(_owner);

  if (pos->y < 40)
    _ecs.getComponent<ECS::Components::Direction>(_owner)->yDirection = 1;
  if (pos->y > 1000)
    _ecs.getComponent<ECS::Components::Direction>(_owner)->yDirection = -1;
}


ECS::Entity SinusoideMove::getID(void) const
{
  return (_owner);
}
