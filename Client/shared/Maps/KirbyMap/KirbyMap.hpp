#pragma once

#include "IMap.hpp"

class KirbyMap : public IMap
{
  private:
    std::pair<int, int> _neededLevel = std::make_pair(0, 5);
    std::string _name = "kirbyMap";

  public:
    KirbyMap(ECS::Manager &ecs, EventManager::Manager &event);
    ~KirbyMap() override;
    const std::string &getName() const override;
    const std::pair<int, int> &getNeededLevel() const override;
    void update(const float time) override;
};

