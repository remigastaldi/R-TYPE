#pragma once

#include <string>
#include <EventManager.hpp>
#include <DynamicLibrary/LibLoader.hpp>
#include "ECS/Manager.hpp"

class IMap
{
  public:
    IMap(ECS::Manager &ecs, EventManager::Manager &event, LibLoader &libloader) {};
    virtual ~IMap() = 0;

    virtual const std::pair<int, int> &getNeededLevel() const = 0;
    virtual void update() = 0;
    virtual bool isEnd() = 0;
};
