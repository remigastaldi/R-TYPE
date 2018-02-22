/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-02-16T11:44:29+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-20T22:43:15+01:00
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
    int _timeBetweenAttack = 100;
    int _curTime = 0;

    int _difficulty = 1;

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
    void update() override;
    ECS::Entity getID() const override;
    void unitOutOfSpace(ECS::Entity entity) override;
};

#ifdef WIN32
extern "C"
{
	char const __declspec(dllexport) *getName()
	{
		return "Metallos";
	}

	IMob __declspec(dllexport) *getSymbol(GameEngine::GameManagers &gameManagers, MapEngine &mapEngine, ECS::Components::Position pos)
	{
		return new Metallos(gameManagers, mapEngine, pos);
	}
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
