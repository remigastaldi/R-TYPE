/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-02-20T17:25:33+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-20T19:49:42+01:00
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

      //std::cout << "entity " << e << "health " << health->health << std::endl;
      if (health->health <= 0)
      {
        getManager().destroyEntity(e);
        _eventManager.fire<int, ECS::Entity>("UnitDie", e);
      }
    }
  }
}
