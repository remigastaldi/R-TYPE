/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-02-16T11:44:29+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-18T13:34:16+01:00
 */


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
    MapEngine &_mapEngine;

    std::string _spriteName;

  public:
    Metallos(GameEngine::GameManagers &gameManagers, MapEngine &mapEngine, ECS::Components::Position pos);
    ~Metallos() override;
    int getDifficulty() const override;
    void playerHit(ECS::Entity by, ECS::Entity to) override;
    void update() override;
    ECS::Entity getID() const override;
    void unitOutOfSpace(ECS::Entity entity) override;
};

#ifdef WIN32
extern "C" char const * __declspec(dllexport) __stdcall getName()
{
  return "Metallos";
}

extern "C" IMob __declspec(dllexport) __stdcall *getSymbol(GameEngine::GameManagers &gameManagers, MapEngine &mapEngine, ECS::Components::Position pos)
{
  return new Metallos(gameManagers, pos);
}

#else

extern "C" char const * getName()
{
  return "Metallos";
}

extern "C" IMob *getSymbol(GameEngine::GameManagers &gameManagers, MapEngine &mapEngine, ECS::Components::Position pos)
{
  return new Metallos(gameManagers, mapEngine, pos);
}

#endif
