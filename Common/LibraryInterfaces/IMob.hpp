  /**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-02-15T15:02:12+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-16T18:40:47+01:00
 */


#pragma once

#include <EventManager.hpp>
#include "ECS/Manager.hpp"
#include <DynamicLibrary/LibLoader.hpp>
#include <GameManagers.hpp>

#include <string>

class IMob
{
  public:
    IMob(GameEngine::GameManagers &, ECS::Components::Position) {};
    virtual ~IMob() = default;

    virtual int getDifficulty() const = 0;
    virtual void playerHit(ECS::Entity, ECS::Entity) = 0;
//    virtual bool isYouWhenHit(ECS::Entity to) = 0;
    virtual void unitOutOfSpace(ECS::Entity) = 0;
    virtual void update() = 0;
    virtual ECS::Entity getID() = 0;
};
