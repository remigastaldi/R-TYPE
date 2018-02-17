/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-02-15T15:02:12+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-17T13:11:20+01:00
 */


#pragma once

#include <string>
#include <EventManager.hpp>
#include <EventManager.hpp>
#include <DynamicLibrary/LibLoader.hpp>
#include "ECS/Manager.hpp"

#include <GameManagers.hpp>

class IMove
{
  public:
    IMove(GameEngine::GameManagers &, ECS::Entity) {};
    virtual ~IMove() = default;

    virtual void update() = 0;
};
