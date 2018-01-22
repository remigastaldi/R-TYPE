#pragma once

#include <LibraryInterfaces/IMob.hpp>
#include <LibraryInterfaces/IAttack.hpp>
#include <LibraryInterfaces/IMove.hpp>
#include "ECS/Components/Components.hpp"
#include "ECS/Components/Stats.hpp"

class Metallos : public IMob
{
  private:
    std::string _ATTACK_NAME = "BasicAttack";
    std::string _MOVE_NAME = "UpAndDownMove";
    std::string _TEXTURE_NAME = "playersSpaceship";
    ECS::Entity _me;
    int _timeBetweenAttack = 20;
    int _curTime = 0;

    int _difficulty = 1;

    //Attacks
    std::unordered_map<ECS::Entity, std::unique_ptr<IAttack *>> _attacks;

    //Move
    std::unique_ptr<IMove *> _movement;

    ECS::Manager &_ecs;
    EventManager::Manager &_event;
    LibLoader &_loader;


  public:
    Metallos(ECS::Manager &ecs, EventManager::Manager &event, LibLoader &loader, ECS::Components::Position pos);
    ~Metallos() override;
    const int getDifficulty() override;
    void playerHit(ECS::Entity by, ECS::Entity to) override;
    void update() override;
    ECS::Entity getID() override;
    void unitOutOfSpace(ECS::Entity entity) override;
};

extern "C" std::string getName()
{
  return "Metallos";
}

extern "C" IMob *getSymbol(ECS::Manager &ecs, EventManager::Manager &event, LibLoader &loader, ECS::Components::Position pos)
{
  return new Metallos(ecs, event, loader, pos);
}

