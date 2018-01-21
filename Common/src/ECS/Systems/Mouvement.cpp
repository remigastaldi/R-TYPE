/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-13T19:04:26+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-21T04:28:54+01:00
 */


#include  "ECS/Systems/Mouvement.hpp"
#include  "ECS/Components/CommonComponents.hpp"
#include <iostream>

namespace ECS
{
  namespace Systems
  {
    Mouvement::Mouvement(ECS::Manager &ecsManager)
      : System(MOUVEMENT_PRIORITY, {ECS::Components::Position::Type, ECS::Components::Direction::Type}, ecsManager)
      {}

    void Mouvement::updateEntity(float delta, Entity e)
    {
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
    }
  }
}
