#pragma once

#include <Maps/ILevels.hpp>

class LevelTwo : public ILevels
{
  private:
    GameEngine::GameManagers &_gameManagers;
    ECS::Manager &_ecs;
    EventManager::Manager &_event;
    LibLoader &_loader;
    MapEngine &_mapEngine;

    bool _isEnd = false;

    int _timeLeft = 0;
    int _timeBetweenMobSpawn = 620;
    int _nbMobSpawn = 10;

    std::unordered_map<ECS::Entity, std::shared_ptr<IMob>> _mobs;

    std::string _name = "LevelTwo";

  public:
    explicit LevelTwo(GameEngine::GameManagers &gameManagers, MapEngine &mapEngine);
    ~LevelTwo() override;
    const std::string &getName() override;
    void enter() override;
    void exit() override;
    bool isEnd() override;
    void update() override;
    int unitOutOfSpace(ECS::Entity entity) override;
    void unitDie(ECS::Entity entity) override;
};
