#pragma once

#include <string>
#include <EventManager.hpp>
#include <DynamicLibrary/LibLoader.hpp>
#include "ECS/Manager.hpp"

class IMob
{
  public:
    IMob(ECS::Manager &ecs, EventManager::Manager &event, LibLoader &libloader, ECS::Components::Position) {};
    virtual ~IMob() = default;

    virtual const int getDifficulty() = 0;
    virtual void playerHit(ECS::Entity, ECS::Entity) = 0;
//    virtual bool isYouWhenHit(ECS::Entity to) = 0;
    virtual void unitOutOfSpace(ECS::Entity) = 0;
    virtual void update() = 0;
    virtual ECS::Entity getID() = 0;
};
