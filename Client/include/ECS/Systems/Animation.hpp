/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-22T07:40:23+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-22T09:47:43+01:00
 */


 #pragma once


#include  "ECS/Manager.hpp"
#include  "ECS/Systems/SystemsPriotity.hpp"

#include  "Resources.hpp"
// #include  "../../Client/include/ECS/Components/Components.hpp"
#include  "ECS/Components/Components.hpp"

#include  "EventManager.hpp"

namespace ECS
{
  namespace Systems
  {
    class Animation : public ECS::System
    {
    public:
      Animation(EventManager::Manager &eventManager, ResourcesManager &resourceManager, ECS::Manager &ecsManager);

      // void update(float delta);
      // void init(void);
      void updateEntity(float delta, Entity e);

    private:
      ResourcesManager &_resourcesManager;
      EventManager::Manager &_eventManager;
   };
  }
}
