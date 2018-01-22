#pragma once

#include <string>
#include <AlfredBase/EventManager/EventManager.hpp>
#include <EventManager.hpp>
#include <DynamicLibrary/LibLoader.hpp>
#include "ECS/Manager.hpp"

class IMove
{
  public:
    IMove(ECS::Manager &ecs, EventManager::Manager &event, LibLoader &, ECS::Entity) {};
    virtual ~IMove() = default;

    virtual void update() = 0;
};

