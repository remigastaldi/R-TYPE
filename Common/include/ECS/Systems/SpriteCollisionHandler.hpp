/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-02-20T15:48:38+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-20T19:47:47+01:00
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
    class SpriteCollisionHandler : public System
    {
    public:
      explicit SpriteCollisionHandler(EventManager::Manager &eventManager, ECS::Manager &ecsManager);

      ~SpriteCollisionHandler() = default;

      void  updateEntity(float delta, Entity e);

    private:
      EventManager::Manager  &_eventManager;
    };
  }
}
