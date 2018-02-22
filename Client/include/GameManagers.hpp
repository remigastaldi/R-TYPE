/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-21T22:16:12+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-21T22:25:43+01:00
 */


#pragma once

#include  "Resources.hpp"
#include  "SoundManager.hpp"

#include  "ECS/Systems/CommonSystems.hpp"
#include  "ECS/Manager.hpp"
#include "ConfigurationManager.hpp"

#include <DynamicLibrary/LibLoader.hpp>

class LibLoader;

namespace GameEngine
{
  struct GameManagers
  {
    GameManagers(ResourcesManager &_resourcesManager, EventManager::Manager &_eventManager,
                 ECS::Manager &_ecsManager, SoundManager &_soundManager, LibLoader &_libraryLoader,
                 ConfigurationManager &configurationManager)
      :
      resources(_resourcesManager),
      event(_eventManager),
      ecs(_ecsManager),
      sound(_soundManager),
      libLoader(_libraryLoader),
      config(configurationManager)
    {}

    ResourcesManager &resources;
    EventManager::Manager &event;
    ECS::Manager &ecs;
    SoundManager &sound;
    LibLoader &libLoader;
    ConfigurationManager &config;
  };
}
