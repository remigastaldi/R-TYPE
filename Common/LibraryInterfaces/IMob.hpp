#pragma once

#include <string>
#include <EventManager.hpp>
#include "ECS/Manager.hpp"

class IMob
{
  public:
    virtual ~IMob() = 0;
    IMob(ECS::Manager &ecs, EventManager::Manager &event) {};

    virtual const int getDifficulty() = 0;
    virtual const std::string &getName() const = 0;
    virtual void update(const float time) = 0;
    virtual ECS::Entity getID() = 0;
};
