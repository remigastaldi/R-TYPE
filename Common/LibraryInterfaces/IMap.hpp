#pragma once

#include <string>
#include <EventManager.hpp>
#include "ECS/Manager.hpp"

class IMap
{
  public:
    virtual ~IMap() = 0;
    IMap(ECS::Manager &ecs, EventManager::Manager &event) {};

    virtual const std::string &getName() const = 0;
    virtual const std::pair<int, int> &getNeededLevel() const = 0;
    virtual void update(const float time) = 0;
};
