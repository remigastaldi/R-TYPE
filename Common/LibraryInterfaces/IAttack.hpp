/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-02-15T15:02:12+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-16T18:39:26+01:00
 */


#pragma once

#include <string>
#include <EventManager.hpp>
#include <DynamicLibrary/LibLoader.hpp>
#include "ECS/Manager.hpp"

class IAttack
{
  public:
    IAttack(GameEngine::GameManagers &, ECS::Entity) {};
    virtual ~IAttack() = default;

    virtual void update() = 0;
    virtual void playerHit(ECS::Entity) = 0;
    virtual ECS::Entity getID() = 0;
};
