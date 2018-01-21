#pragma once

#include <string>
#include <AlfredBase/EventManager/EventManager.hpp>
#include <EventManager.hpp>
#include "ECS/Manager.hpp"

class IMove
{
  public:
    virtual ~IMove() = 0;
    virtual IMove(ECS::Manager &ecs, EventManager::Manager &event) {};

    virtual const std::string &getName() const = 0;
    virtual void update(const float time) = 0;
};

