/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-13T19:04:26+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-22T00:27:08+01:00
 */


#include  "ECS/Systems/Mouvement.hpp"

namespace ECS
{
  namespace Systems
  {
    Mouvement::Mouvement(EventManager::Manager &eventManager, ECS::Manager &ecsManager)
      : System(MOUVEMENT_PRIORITY, {Alfred::Utils::GetTypeID<ECS::Components::Position>(), Alfred::Utils::GetTypeID<ECS::Components::Direction>()}, ecsManager),
      _eventManager(eventManager)
      {
        _eventManager.addEvent<void, ECS::Entity>("UnitOutOfSpace");
      }

    void Mouvement::updateEntity(float delta, Entity e)
    {
      (void) delta;
      std::shared_ptr<ECS::Components::Position> position = getManager().getComponent<ECS::Components::Position>(e);
      std::shared_ptr<ECS::Components::Direction> direction = getManager().getComponent<ECS::Components::Direction>(e);


      if (direction->xDirection != 0)
      {
        position->x += (direction->xDirection * direction->speed);
      }
      if (direction->yDirection != 0)
      {
        position->y += (direction->yDirection * direction->speed);
      }

      if ((position->x <= 0 || position->x >= 1900) || (position->y <= 0 || position->y >= 1080))
      {
        _eventManager.fire<void, ECS::Entity>("UnitOutOfSpace", e);
        getManager().destroyEntity(e);
      }
    }
  }
}
