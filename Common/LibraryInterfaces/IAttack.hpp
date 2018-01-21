#pragma once

#include <string>
#include <EventManager.hpp>
#include "ECS/Manager.hpp"

class IAttack
{
  public:
    IAttack(ECS::Manager &ecs, EventManager::Manager &event) {};
    virtual ~IAttack() = 0;

    virtual const std::string &getName() const = 0;
    virtual void update(const float time) = 0;
    virtual void playerHit(ECS::Entity) = 0;
    virtual ECS::Entity getID() = 0;
    virtual void giveOwnerEntity(ECS::Entity) = 0;
};