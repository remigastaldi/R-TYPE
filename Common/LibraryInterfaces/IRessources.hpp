#pragma once

#include <string>
#include <map>
#include "RessourcesManager.hpp"

class IRessources
{
  public:
    virtual ~IRessources() = 0;

    virtual const std::string &getName() const = 0;

    virtual void registerRessources(RessourceManager::Manager &) = 0;
};

