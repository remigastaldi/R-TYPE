#pragma once

#include "IAttack.hpp"
#include "ECS/Components/Stats.hpp"

class BasicAttack : public IAttack
{
  private:
    ECS::Manager &_ecs;
    EventManager::Manager &_event;

    std::string _name = "BasicAttack";
    bool _eventSet = false;
    int _baseDamage = 1;
    ECS::Entity _entity;

  public:
    BasicAttack(ECS::Manager &ecs, EventManager::Manager &event);
    ~BasicAttack() override;
    const std::string &getName() const override;
    void update(const float time) override;
};

