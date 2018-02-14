#include "StraightMove.hpp"

StraightMove::StraightMove(GameEngine::GameManagers &gameManagers, ECS::Entity entity) :
  IMove(gameManagers, entity),
  _gameManagers(gameManagers),
  _ecs(gameManagers.ecs),
  _event(gameManagers.event),
  _loader(gameManagers.libLoader),
  _owner(entity)
{
  _ecs.addComponent<ECS::Components::Direction>(_owner, ECS::Components::Direction(-1, 0, 20));

  _ecs.updateEntityToSystems(_owner);
}

StraightMove::~StraightMove() = default;

void StraightMove::update()
{
  //go straight so nothing to do
}
