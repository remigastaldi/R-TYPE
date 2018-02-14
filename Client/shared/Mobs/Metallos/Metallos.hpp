#pragma once

#include <LibraryInterfaces/IMob.hpp>
#include <LibraryInterfaces/IAttack.hpp>
#include <LibraryInterfaces/IMove.hpp>
#include "ECS/Components/Components.hpp"
#include "ECS/Components/Stats.hpp"

#include <Resources.hpp>

class Metallos : public IMob
{
  private:
    std::string _ATTACK_NAME = "BasicAttack";
    std::string _MOVE_NAME = "UpAndDownMove";
    std::string _TEXTURE_NAME = "MetallosSprite";
    ECS::Entity _me;
    int _timeBetweenAttack = 60;
    int _curTime = 0;

    int _difficulty = 1;

    //Attacks
    std::unordered_map<ECS::Entity, std::shared_ptr<IAttack>> _attacks;

    //Move
    std::shared_ptr<IMove> _movement;

    GameEngine::GameManagers &_gameManagers;
    ECS::Manager &_ecs;
    EventManager::Manager &_event;
    LibLoader &_loader;

    std::string _spriteName;

  public:
    Metallos(GameEngine::GameManagers &gameManagers, ECS::Components::Position pos);
    ~Metallos() override;
    const int getDifficulty() override;
    void playerHit(ECS::Entity by, ECS::Entity to) override;
    void update() override;
    ECS::Entity getID() override;
    void unitOutOfSpace(ECS::Entity entity) override;
};

#if WIN32
extern "C" std::string __declspec(dllexport) __stdcall getName()
{
  return "Metallos";
}

extern "C" IMob __declspec(dllexport) __stdcall *getSymbol(GameEngine::GameManagers &gameManagers, ECS::Components::Position pos)
{
  return new Metallos(gameManagers, pos);
}

#else

extern "C" std::string getName()
{
  return "Metallos";
}

extern "C" IMob *getSymbol(GameEngine::GameManagers &gameManagers, ECS::Components::Position pos)
{
  return new Metallos(gameManagers, pos);
}

#endif
