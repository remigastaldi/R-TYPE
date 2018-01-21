#pragma once

#include <LibraryInterfaces/IMove.hpp>
#include "IAttack.hpp"
#include "ECS/Components/Stats.hpp"

class BasicAttack : public IAttack
{
  private:
    ECS::Manager &_ecs;
    EventManager::Manager &_event;

    std::string _name = "BasicAttack";
    int _baseDamage = 1;
    ECS::Entity _entity;
    float _precTime = 0;
    float _timeLeft = 0;
    float _timeBetweenHit = 100;
    std::vector<ECS::Entity> _attacks;
    ECS::Entity _ownerEntity;

    std::vector<IMove *> _move;

  private:
    void attack();

  public:
    BasicAttack(ECS::Manager &ecs, EventManager::Manager &event);
    ~BasicAttack() override;
    const std::string &getName() const override;
    void update(const float time) override;
    void playerHit(ECS::Entity entity) override;
    ECS::Entity getID() override;
    void giveOwnerEntity(ECS::Entity entity) override;
    void move();
};

