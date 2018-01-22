/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-21T04:43:38+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-22T05:31:44+01:00
 */


#pragma once


#include  "ECS/Manager.hpp"
#include  "ECS/Systems/SystemsPriotity.hpp"
#include  "ECS/Components/CommonComponents.hpp"

#include  "../../Client/include/Resources.hpp"
#include  "../../Client/include/ECS/Components/Components.hpp"

#include  "EventManager.hpp"

namespace ECS
{
  namespace Systems
  {
    class Collision : public ECS::System
    {
    public:
      Collision(EventManager::Manager &eventManager, ResourcesManager &resourceManager, ECS::Manager &manager);

      // void update(float delta);
      void init(void);
      void updateEntity(float delta, Entity e);

    private:
      ResourcesManager &_resourcesManager;
      EventManager::Manager &_eventManager;
    };
  }
}
