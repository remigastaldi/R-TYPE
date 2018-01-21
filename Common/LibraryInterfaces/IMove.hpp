#pragma once

#include <string>
#include <AlfredBase/EventManager/EventManager.hpp>
#include <EventManager.hpp>
#include "ECS/Manager.hpp"

class IMove
{
  public:
    IMove(ECS::Manager &ecs, EventManager::Manager &event) {};
    virtual ~IMove() = 0;

    virtual void giveOwnerEntity(ECS::Entity) = 0;
    virtual ECS::Entity getID() = 0;
    virtual const std::string &getName() const = 0;
    virtual void update(const float time) = 0;
};

