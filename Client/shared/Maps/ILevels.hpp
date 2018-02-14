#pragma once

#include <string>
#include <DynamicLibrary/LibLoader.hpp>
#include "IMove.hpp"
#include "IMob.hpp"
#include "IAttack.hpp"
#include <EventManager.hpp>

class ILevels
{
  public:
    ILevels(GameEngine::GameManagers &gameManagers)
    {}

    virtual ~ILevels()
    {}

    virtual const std::string &getName() = 0;

    virtual void enter() = 0;
    virtual void exit() = 0;
    virtual bool isEnd() = 0;
    virtual void update() = 0;
    virtual void playerHit(ECS::Entity, ECS::Entity) = 0;
    virtual void unitOutOfSpace(ECS::Entity) = 0;
};
