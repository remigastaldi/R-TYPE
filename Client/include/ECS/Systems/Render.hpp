/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-20T04:48:40+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-20T19:13:55+01:00
 */


#pragma once

#include  "ECS/Manager.hpp"

#include  "ECS/Systems/SystemsPriotity.hpp"


namespace ECS
{
  namespace Systems
  {
    class Render : public System
    {
    public:
      explicit Render(ECS::Manager &manager);

      // void update(float delta);
      void updateEntity(float delta, Entity e);
    };
  }
}
