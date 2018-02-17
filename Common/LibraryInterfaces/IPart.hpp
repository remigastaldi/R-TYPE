/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-02-16T14:09:59+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-17T13:11:26+01:00
 */


#pragma once

#include <string>
#include <EventManager.hpp>
#include "ECS/Manager.hpp"

namespace Part
{
    enum ShipPart
    {
        COCKPIT = 0,
        THRUSTER,
        SHIELD,
        GUN,
        POWERUP
    };
}

class IPart
{
  public:
    virtual ~IPart() = 0;

    virtual const std::string &getName() const = 0;
    virtual const Part::ShipPart &getPartType() const = 0;
    virtual void update(const float time, ECS::Manager &ecs, Alfred::EventManager::Manager &event) = 0;

    virtual const int getWeight() = 0;
    virtual const int getPrice() = 0;
    virtual const int getHealth() = 0;
    virtual void setHealth(const int) = 0;

    virtual const std::string &getSpriteName() = 0;

    virtual const int getSpeedModifier() {
        return 0;
    };
};
