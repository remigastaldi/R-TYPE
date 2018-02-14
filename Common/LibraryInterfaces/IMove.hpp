#pragma once

#include <string>
#include <AlfredBase/EventManager/EventManager.hpp>
#include <EventManager.hpp>
#include <DynamicLibrary/LibLoader.hpp>
#include "ECS/Manager.hpp"

#include <GameManagers.hpp>

class IMove
{
  public:
    IMove(GameEngine::GameManagers &gameManagers, ECS::Entity) {};
    virtual ~IMove() = default;

    virtual void update() = 0;
};
