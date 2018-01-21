/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-21T04:36:33+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-21T08:11:12+01:00
 */


#include  "ECS/Systems/Collision.hpp"

#include  "ECS/Components/CommonComponents.hpp"
#include <iostream>

namespace ECS
{
  namespace Systems
  {
    Collision::Collision(ECS::Manager &ecsManager)
      : System(COLLISION_PRIORITY, {Alfred::Utils::GetTypeID<ECS::Components::Position>(), Alfred::Utils::GetTypeID<ECS::Components::Collisionable>(),
          Alfred::Utils::GetTypeID<ECS::Components::Drawable>()}, ecsManager)
      { }

    void Collision::updateEntity(float delta, Entity e)
    {
      std::shared_ptr<ECS::Components::Position> position = getManager().getComponent<ECS::Components::Position>(e);
    }
  }
}
