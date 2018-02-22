/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-02-16T14:10:00+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-17T13:11:34+01:00
 */


#pragma once

#include <string>
#include <vector>
#include <EventManager.hpp>
#include "ECS/Manager.hpp"
#include "IPart.hpp"

using blueprint_part = std::vector<std::vector<std::pair<IPart *, Part::ShipPart>>>;

class IShipBlueprint
{
  public:
    virtual ~IShipBlueprint() = 0;

    virtual const std::string &getName() const = 0;
    virtual void update(const float time, ECS::Manager &ecs, Alfred::EventManager::Manager &event) = 0;
    virtual const int getPrice() = 0;
};
