#pragma once

#include <string>
#include <AlfredBase/EventManager/EventManager.hpp>
#include "ECS/Manager.hpp"

class IScene
{
  public:
    virtual ~IScene() = 0;

    virtual const std::string &getName() const = 0;

    virtual void onEnter() = 0;
    virtual void onExit() = 0;

    virtual void onPause() = 0;
    virtual void onResume() = 0;

    virtual void update(const float time, ECS::Manager &ecs, Alfred::EventManager::Manager &event) = 0;
};

