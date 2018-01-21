#pragma once

#include <string>
#include <EventManager.hpp>
#include "ECS/Manager.hpp"

class IAttack
{
  public:
    virtual ~IAttack() = 0;
    virtual IAttack(ECS::Manager &ecs, EventManager::Manager &event) {};

    virtual const std::string &getName() const = 0;
    virtual void update(const float time) = 0;
};