/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-13T19:02:40+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-21T23:57:57+01:00
 */


#pragma once

#include  "ECS/Manager.hpp"
#include  "ECS/Systems/SystemsPriotity.hpp"
#include  "ECS/Components/CommonComponents.hpp"

#include  "EventManager.hpp"

namespace ECS
{
  namespace Systems
  {
    class Mouvement : public ECS::System
    {
    public:
      Mouvement(EventManager::Manager &eventManager, ECS::Manager &manager);

      // void update(float delta);
      void updateEntity(float delta, Entity e);

    private:
      EventManager::Manager  &_eventManager;
    };
  }
}
