#pragma once

#include <string>
#include <EventManager.hpp>
#include <DynamicLibrary/LibLoader.hpp>
#include "ECS/Manager.hpp"

class IAttack
{
  public:
    IAttack(ECS::Manager &ecs, EventManager::Manager &event, LibLoader &libloader, ECS::Entity) {};
    virtual ~IAttack() = default;

    virtual void update() = 0;
    virtual void playerHit(ECS::Entity) = 0;
    virtual ECS::Entity getID() = 0;
};