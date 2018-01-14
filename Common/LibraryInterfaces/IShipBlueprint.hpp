#pragma once

#include <string>
#include <vector>
#include <AlfredBase/EventManager/EventManager.hpp>
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

