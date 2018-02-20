/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-02-20T14:16:40+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-20T15:11:47+01:00
 */


#pragma once

#include  "Utils.hpp"

#include  "ECS/Manager.hpp"
#include  "ECS/Systems/SystemsPriotity.hpp"
#include  "ECS/Components/CommonComponents.hpp"

#include  "EventManager.hpp"

namespace ECS
{
  namespace Systems
  {
    class CleanupFrameCollisionComponents : public ECS::System
    {
    public:
      explicit CleanupFrameCollisionComponents(ECS::Manager &ecsManager);
      ~CleanupFrameCollisionComponents();

      void  updateEntity(float delta, Entity e);

    private:

    };
  }
}
