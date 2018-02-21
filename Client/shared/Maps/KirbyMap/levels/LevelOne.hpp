/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-02-15T15:02:13+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-20T22:43:57+01:00
 */


#pragma once

#include <Maps/ILevels.hpp>

class LevelOne : public ILevels
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
    int _nbMobSpawn = 2;

    std::unordered_map<ECS::Entity, std::shared_ptr<IMob>> _mobs;

    std::string _name = "LevelOne";

  public:
    explicit LevelOne(GameEngine::GameManagers &gameManagers, MapEngine &mapEngine);
    ~LevelOne() override;
    const std::string &getName() override;
    void enter() override;
    void exit() override;
    bool isEnd() override;
    void update() override;
    int unitOutOfSpace(ECS::Entity entity) override;
    void unitDie(ECS::Entity entity) override;
};
