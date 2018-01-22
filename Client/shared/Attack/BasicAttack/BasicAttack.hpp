#pragma once

#include <LibraryInterfaces/IMove.hpp>
#include "IAttack.hpp"
#include "ECS/Components/Stats.hpp"

class BasicAttack : public IAttack
{
  private:
    std::string _TEXTURE = "playersMissiles";
//    std::string _MOVE = "SinusoideMove";
    std::string _MOVE = "StraightMove";
    ECS::Manager &_ecs;
    EventManager::Manager &_event;
    LibLoader &_loader;

    int _baseDamage = 1;
    ECS::Entity _entity;

    std::vector<ECS::Entity> _attacks;
    ECS::Entity _ownerEntity;

    std::unique_ptr<IMove *> _move;

  public:
    BasicAttack(ECS::Manager &ecs, EventManager::Manager &event, LibLoader &loader, ECS::Entity owner);
    ~BasicAttack() override;
    void update() override;
    void playerHit(ECS::Entity entity) override;
    ECS::Entity getID() override;
    void move();
};

#if WIN32
extern "C" std::string __declspec(dllexport) __stdcall getName()
{
  return "BasicAttack";
}

extern "C" IAttack  __declspec(dllexport) __stdcall *getSymbol(ECS::Manager &ecs, EventManager::Manager &event, LibLoader &loader, ECS::Entity parent)
{
  return new BasicAttack(ecs, event, loader, parent);
}

#else

extern "C" std::string getName()
{
  return "BasicAttack";
}

extern "C" IAttack *getSymbol(ECS::Manager &ecs, EventManager::Manager &event, LibLoader &loader, ECS::Entity parent)
{
  return new BasicAttack(ecs, event, loader, parent);
}

#endif