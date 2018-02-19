/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-02-15T15:02:12+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-19T15:04:01+01:00
 */


#pragma once

#include "MapEngine.hpp"

#include <EventManager.hpp>
#include <DynamicLibrary/LibLoader.hpp>
#include "ECS/Manager.hpp"

#include <string>

#include <GameManagers.hpp>

class IMove : virtual public IEntityObject
{
  public:
    IMove(GameEngine::GameManagers &, ECS::Entity) {};
    virtual ~IMove() = default;
};
