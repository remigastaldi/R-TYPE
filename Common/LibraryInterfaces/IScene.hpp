/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-19T18:05:32+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-19T21:41:18+01:00
 */


#pragma once

#include "ECS/Manager.hpp"
#include "EventManager.hpp"
#include <string>

class IScene
{
  public:
    virtual ~IScene() {};

    virtual const std::string &getName() const = 0;

    virtual void onEnter() = 0;
    virtual void onExit() = 0;

    virtual void onPause() = 0;
    virtual void onResume() = 0;

    virtual void update(const float time, ECS::Manager &ecs, EventManager::Manager &event) = 0;
};
