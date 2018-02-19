/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-02-15T15:02:12+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-16T18:39:26+01:00
 */


#pragma once

#include  "MapEngine.hpp"

#include <string>
#include <EventManager.hpp>
#include <DynamicLibrary/LibLoader.hpp>
#include "ECS/Manager.hpp"

class IAttack : virtual public IEntityObject
{
  public:
    IAttack(GameEngine::GameManagers &, MapEngine &, ECS::Entity) {};
    virtual ~IAttack() = default;

    virtual void playerHit(ECS::Entity) = 0;
};
