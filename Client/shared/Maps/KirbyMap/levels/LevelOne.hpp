#pragma once

#include <Maps/ILevels.hpp>

class LevelOne : public ILevels
{
  private:
    ECS::Manager &_ecs;
    EventManager::Manager &_event;
    LibLoader &_loader;

    bool _isEnd = false;

    int _timeLeft;
    int _timeBetweenMobSpawn = 320;
    int _nbMobSpawn = 2;

    std::unordered_map<ECS::Entity, std::unique_ptr<IMob *>> _mobs;

    std::string _name = "LevelOne";

  public:
    LevelOne(ECS::Manager &ecs, EventManager::Manager &event, LibLoader &libloader);
    ~LevelOne() override;
    const std::string &getName() override;
    void enter() override;
    void exit() override;
    bool isEnd() override;
    void update() override;
    void playerHit(ECS::Entity by, ECS::Entity to) override;
};

