#pragma once

#include <Maps/ILevels.hpp>

class LevelThree : public ILevels
{
  private:
    GameEngine::GameManagers &_gameManagers;
    ECS::Manager &_ecs;
    EventManager::Manager &_event;
    LibLoader &_loader;
    MapEngine &_mapEngine;

    bool _isEnd = false;

    int _timeLeft = 0;
    int _timeBetweenMobSpawn = 320;
    int _nbMobSpawn = 4;

    std::string _name = "LevelThree";

  public:
    explicit LevelThree(GameEngine::GameManagers &gameManagers, MapEngine &mapEngine);
    ~LevelThree() override;
    const std::string &getName() override;
    void enter() override;
    void exit() override;
    bool isEnd() override;
    void update() override;
    int unitOutOfSpace(ECS::Entity entity) override;
    void unitDie(ECS::Entity entity) override;
};
