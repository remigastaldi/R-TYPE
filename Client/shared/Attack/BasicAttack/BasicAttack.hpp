#pragma once

#include <LibraryInterfaces/IMove.hpp>
#include "IAttack.hpp"
#include <ECS/Components/Components.hpp>
#include "ECS/Components/Stats.hpp"

#include <Resources.hpp>

class BasicAttack : public IAttack
{
  private:
    GameEngine::GameManagers &_gameManagers;
    ECS::Manager &_ecs;
    EventManager::Manager &_event;
    LibLoader &_loader;
    ECS::Entity _ownerEntity;

    std::string _TEXTURE = "playersMissiles";
//    std::string _MOVE = "SinusoideMove";
    std::string _MOVE = "StraightMove";


    int _baseDamage = 1;
    ECS::Entity _entity;

    std::vector<ECS::Entity> _attacks;

    std::shared_ptr<IMove> _move;

    std::string _spriteName;

  public:
    BasicAttack(GameEngine::GameManagers &gameManagers, ECS::Entity owner);
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

extern "C" IAttack  __declspec(dllexport) __stdcall *getSymbol(GameEngine::GameManagers &gameManagers, ECS::Entity parent)
{
  return new BasicAttack(gameManagers);
}

#else

extern "C" std::string getName()
{
  return "BasicAttack";
}

extern "C" IAttack *getSymbol(GameEngine::GameManagers &gameManagers, ECS::Entity parent)
{
  return new BasicAttack(gameManagers, parent);
}

#endif
