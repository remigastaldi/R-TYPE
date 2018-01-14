/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-13T19:02:40+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-13T23:42:13+01:00
 */


#pragma once

#include  "ECS/Manager.hpp"

#include  "ECS/Systems/SystemsPriotity.hpp"

namespace ECS
{
  class Mouvement : public ECS::System
  {
  public:
    Mouvement(std::observer_ptr<ECS::Manager> &manager);

    // void update(float delta);
    void updateEntity(float delta, Entity e);
  };
}
