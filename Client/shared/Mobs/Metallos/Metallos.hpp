#pragma once

#include <LibraryInterfaces/IMob.hpp>
#include <LibraryInterfaces/IAttack.hpp>

class Metallos : public IMob
{
  private:
    std::string _name = "Metallos";
    ECS::Entity _me;

    int _difficulty = 1;

    IAttack *_attack;

    ECS::Manager &_ecs;
    EventManager::Manager &_event;


  public:
    Metallos(ECS::Manager &ecs, EventManager::Manager &event);
    ~Metallos() override;
    const int getDifficulty() override;
    void playerHit(ECS::Entity entity) override;
    const std::string &getName() const override;
    void update(const float time) override;
    ECS::Entity getID() override;
};

