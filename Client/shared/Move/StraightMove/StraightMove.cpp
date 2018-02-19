/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-02-19T14:30:27+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-19T18:17:39+01:00
 */


#include "StraightMove.hpp"

StraightMove::StraightMove(GameEngine::GameManagers &gameManagers, ECS::Entity entity, int direction, int speed) :
  IMove(gameManagers, entity),
  _gameManagers(gameManagers),
  _ecs(gameManagers.ecs),
  _event(gameManagers.event),
  _loader(gameManagers.libLoader),
  _owner(entity)
{
  _ecs.addComponent<ECS::Components::Direction>(_owner, ECS::Components::Direction(direction, 0, speed));

  _ecs.updateEntityToSystems(_owner);
}

StraightMove::~StraightMove()
{
  _ecs.extractComponent<ECS::Components::Direction>(_owner);
  _ecs.updateEntityToSystems(_owner);
}

void StraightMove::update()
{
  //go straight so nothing to do
}

ECS::Entity StraightMove::getID(void) const
{
  return (_owner);
}
