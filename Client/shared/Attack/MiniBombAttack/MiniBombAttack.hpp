#pragma once

#include <LibraryInterfaces/IMove.hpp>
#include "IAttack.hpp"
#include <ECS/Components/Components.hpp>
#include "ECS/Components/Stats.hpp"

#include <Resources.hpp>

class MiniBombAttack : public IAttack
{
  private:
    int _beforeExplosion;
    GameEngine::GameManagers &_gameManagers;
    ECS::Manager &_ecs;
    EventManager::Manager &_event;
    LibLoader &_loader;
    MapEngine   &_mapEngine;

    ECS::Entity _ownerEntity;

    std::string _TEXTURE = "mini_bomb_texture";

    int _baseDamage = 0;
    ECS::Entity _entity;

    std::vector<ECS::Entity> _attacks;

    std::shared_ptr<IMove> _move;

    std::string _spriteName;

    EventManager::EventListener toDel;

  public:
    MiniBombAttack(GameEngine::GameManagers &gameManagers, MapEngine &mapEngine, ECS::Entity owner);
    ~MiniBombAttack() override;
    void update() override;
    ECS::Entity getID() const override;
    void move();
};

#ifdef WIN32
extern "C"
{
	char const  __declspec(dllexport) *getName()
	{
		return "MiniBombAttack";
	}

	IAttack  __declspec(dllexport) *getSymbol(GameEngine::GameManagers &gameManagers, MapEngine &mapEngine, ECS::Entity parent)
	{
		return new MiniBombAttack(gameManagers, mapEngine, parent);
	}
}
#else

extern "C" char const * getName()
{
  return "MiniBombAttack";
}

extern "C" IAttack *getSymbol(GameEngine::GameManagers &gameManagers, MapEngine &mapEngine, ECS::Entity parent)
{
  return new MiniBombAttack(gameManagers, mapEngine, parent);
}

#endif