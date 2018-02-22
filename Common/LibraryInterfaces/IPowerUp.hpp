/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-02-16T14:09:59+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-17T13:11:51+01:00
 */


#pragma once

#include <string>
#include <EventManager.hpp>
#include "ECS/Manager.hpp"

class IPowerUp
{
  public:
    virtual ~IPowerUp() = 0;

    virtual const std::string &getName() const = 0;
    virtual void update(const float time, ECS::Manager &ecs, Alfred::EventManager::Manager &event) = 0;
};
