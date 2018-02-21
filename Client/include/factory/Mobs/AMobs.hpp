#pragma once

#include <LibraryInterfaces/IMob.hpp>
#include <LibraryInterfaces/IAttack.hpp>
#include <LibraryInterfaces/IMove.hpp>
#include "ECS/Components/Components.hpp"
#include "ECS/Components/Stats.hpp"

#include <Resources.hpp>

class AMobs : public IMob
{
  private:
    std::string _ATTACK_NAME;
    std::string _MOVE_NAME;
    std::string _TEXTURE_NAME;
    ECS::Entity _me;
    int _timeBetweenAttack = 100;
    int _curTime = 0;

    int _difficulty = 1;

    GameEngine::GameManagers &_gameManagers;
    ECS::Manager &_ecs;
    EventManager::Manager &_event;
    LibLoader &_loader;
    MapEngine &_mapEngine;

    std::string _spriteName;

  public:
    AMobs(GameEngine::GameManagers &gameManagers, MapEngine &mapEngine, ECS::Components::Position pos, std::string attack_name, std::string movement_name, std::string texture_name);
    ~AMobs() override;
    int getDifficulty() const override;
    void update() override;
    ECS::Entity getID() const override;
    void unitOutOfSpace(ECS::Entity entity) override;
};