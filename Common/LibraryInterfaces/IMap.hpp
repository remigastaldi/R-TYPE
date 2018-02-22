#pragma once

#include <string>
#include <EventManager.hpp>
#include <DynamicLibrary/LibLoader.hpp>
#include "ECS/Manager.hpp"

class IMap
{
  public:
    IMap() {};
    virtual ~IMap() = default;

    virtual const std::pair<int, int> &getNeededLevel() const = 0;
    virtual void update() = 0;
    virtual bool isEnd() = 0;
};
