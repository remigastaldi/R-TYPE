/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-02-16T18:03:51+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-17T12:48:39+01:00
 */


#pragma once

#include <string>
#include <DynamicLibrary/LibLoader.hpp>
#include "IMove.hpp"
#include "IMob.hpp"
#include "IAttack.hpp"
#include <EventManager.hpp>

class ILevels
{
  public:
    ILevels(GameEngine::GameManagers &)
    {}

    virtual ~ILevels()
    {}

    virtual const std::string &getName() = 0;

    virtual void enter() = 0;
    virtual void exit() = 0;
    virtual bool isEnd() = 0;
    virtual void update() = 0;
    virtual void playerHit(ECS::Entity, ECS::Entity) = 0;
    virtual void unitOutOfSpace(ECS::Entity) = 0;
};
