#pragma once

#include <AlfredBase/EventManager/EventManager.hpp>
#include "RessourcesManager.hpp"
#include "SceneManager.hpp"

static constexpr char GE_DEFAULT_LOG_PATH[] = ".";
static constexpr char GE_DEFAULT_RESSOURCES_PATH[] = "Ressources";

namespace GameEngine
{
    class Engine
    {
      private:
        Alfred::EventManager::Manager _eventManager;
        RessourceManager::Manager _ressourcesManager;
        SceneManager _sceneManager;
        //TODO Graphic Manager
        //TODO GUI Manager
        //TODO .SO loader
        //TODO network manager

      public:
        Engine();

        void initLog(const std::string &path = GE_DEFAULT_LOG_PATH);
        void loadDynamicLibrary(const std::string &path = GE_DEFAULT_RESSOURCES_PATH);
    };
}

