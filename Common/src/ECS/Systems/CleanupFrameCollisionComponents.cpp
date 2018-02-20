/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-02-20T14:15:44+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-20T15:43:37+01:00
 */


#include  "ECS/Systems/CleanupFrameCollisionComponents.hpp"

namespace ECS
{
  namespace Systems
  {
    CleanupFrameCollisionComponents::CleanupFrameCollisionComponents(ECS::Manager &ecsManager)
      : System(CLEANUP_FRAME_COLLISION_COMPONENTS, { ecsManager.GetTypeID<ECS::Components::CollisionFrame>() }, ecsManager)
    { }

    CleanupFrameCollisionComponents::~CleanupFrameCollisionComponents()
    {}

    void  CleanupFrameCollisionComponents::updateEntity(float delta, Entity e)
    {
      (void) delta;

      //std::shared_ptr<ECS::Components::Collisionable> = getManager().getComponent<ECS::Components::Collisionable>(e);
      std::shared_ptr<ECS::Components::CollisionFrame> collisionFrame = getManager().getComponent<ECS::Components::CollisionFrame>(e);

      collisionFrame->nbFrames--;

      if (collisionFrame == 0)
        getManager().extractComponent<ECS::Components::CollisionFrame>(e);
    }
  }
}
