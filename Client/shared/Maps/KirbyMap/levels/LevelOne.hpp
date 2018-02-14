#pragma once

#include <Maps/ILevels.hpp>

class LevelOne : public ILevels
{
  private:
    GameEngine::GameManagers &_gameManagers;
    ECS::Manager &_ecs;
    EventManager::Manager &_event;
    LibLoader &_loader;

    bool _isEnd = false;

    int _timeLeft = 0;
    int _timeBetweenMobSpawn = 320;
    int _nbMobSpawn = 2;

    std::unordered_map<ECS::Entity, std::shared_ptr<IMob>> _mobs;

    std::string _name = "LevelOne";

  public:
    LevelOne(GameEngine::GameManagers &gameManagers);
    ~LevelOne() override;
    const std::string &getName() override;
    void enter() override;
    void exit() override;
    bool isEnd() override;
    void update() override;
    void playerHit(ECS::Entity by, ECS::Entity to) override;
    void unitOutOfSpace(ECS::Entity entity) override;
};
