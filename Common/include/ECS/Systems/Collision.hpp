/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-21T04:43:38+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-22T02:46:29+01:00
 */


#pragma once


#include  "ECS/Manager.hpp"
#include  "ECS/Systems/SystemsPriotity.hpp"
#include  "ECS/Components/CommonComponents.hpp"

#include  "../../Client/include/Resources.hpp"
#include  "../../Client/include/ECS/Components/Components.hpp"

namespace ECS
{
  namespace Systems
  {
    class Collision : public ECS::System
    {
    public:
      Collision(ResourcesManager &resourceManager, ECS::Manager &manager);

      // void update(float delta);
      void updateEntity(float delta, Entity e);

    private:
      ResourcesManager &_resourcesManager;
    };
  }
}
