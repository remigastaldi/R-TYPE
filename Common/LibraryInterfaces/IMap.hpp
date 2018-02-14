#pragma once

#include <string>
#include <EventManager.hpp>
#include <DynamicLibrary/LibLoader.hpp>
#include "ECS/Manager.hpp"

#include <GameManagers.hpp>

class IMap
{
  public:
    IMap(GameEngine::GameManagers &gameManagers) {};
    virtual ~IMap() = default;

    virtual const std::pair<int, int> &getNeededLevel() const = 0;
    virtual void update() = 0;
    virtual bool isEnd() = 0;
};
