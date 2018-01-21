#pragma once

#include <LibraryInterfaces/IMob.hpp>
#include "IMap.hpp"

class KirbyMap : public IMap
{
  private:
    std::pair<int, int> _neededLevel = std::make_pair(0, 5);
    std::string _name = "kirbyMap";

    int _wave = 0;

    std::unordered_map<ECS::Entity, IMob *> _mobs;

    ECS::Manager &_ecs;
    EventManager::Manager &_event;

  public:
    KirbyMap(ECS::Manager &ecs, EventManager::Manager &event);
    ~KirbyMap() override;
    const std::string &getName() const override;
    const std::pair<int, int> &getNeededLevel() const override;
    void update(const float time) override;
};

