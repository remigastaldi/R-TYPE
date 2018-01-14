#pragma once

#include <string>
#include <AlfredBase/EventManager/EventManager.hpp>
#include "ECS/Manager.hpp

class IPowerUp
{
  public:
    virtual ~IPowerUp() = 0;

    virtual const std::string &getName() const = 0;
    virtual void update(const float time, ECS::Manager &ecs, Alfred::EventManager::Manager &event) = 0;
};

