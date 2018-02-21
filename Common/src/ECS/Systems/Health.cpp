/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-02-20T17:25:33+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-21T02:56:03+01:00
 */


#include  "ECS/Systems/Health.hpp"

namespace ECS
{
  namespace Systems
  {
    Health::Health(EventManager::Manager &eventManager, ECS::Manager &ecsManager)
      : System(HEALTH_PRIORITY, { ecsManager.GetTypeID<ECS::Components::Health>() }, ecsManager),
      _eventManager(eventManager)
    {}

    void  Health::updateEntity(float delta, Entity e)
    {
      (void) delta;

      std::shared_ptr<ECS::Components::Health>  health(getManager().getComponent<ECS::Components::Health>(e));

      // std::cout << "entity " << e << "health " << health->health << std::endl;
      std::shared_ptr<ECS::Components::CollisionFrame>  collisionFrame(getManager().getComponent<ECS::Components::CollisionFrame>(e));
      if (collisionFrame.get() != nullptr)
      {
        std::shared_ptr<ECS::Components::Player>  player(getManager().getComponent<ECS::Components::Player>(e));
        if (player.get() != nullptr)
        {
          _eventManager.fire<int, const std::string &, int>("changePlayerHealth", player->name, health->health);
        }
      }

      if (health->health <= 0)
      {
        getManager().destroyEntity(e);
        _eventManager.fire<int, ECS::Entity>("UnitDieEvent", e);
      }
    }
  }
}
