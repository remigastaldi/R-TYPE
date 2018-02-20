/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-02-16T18:03:51+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-20T22:42:27+01:00
 */


#pragma once

#include "IMove.hpp"
#include "IMob.hpp"
#include "IAttack.hpp"

#include <DynamicLibrary/LibLoader.hpp>
#include <EventManager.hpp>
#include <MapEngine.hpp>

#include <string>

class ILevels
{
  public:
    ILevels(GameEngine::GameManagers &, MapEngine &)
    {}

    virtual ~ILevels()
    {}

    virtual const std::string &getName() = 0;

    virtual void enter() = 0;
    virtual void exit() = 0;
    virtual bool isEnd() = 0;
    virtual void update() = 0;
    virtual void unitOutOfSpace(ECS::Entity) = 0;
    virtual void unitDie(ECS::Entity) = 0;
};
