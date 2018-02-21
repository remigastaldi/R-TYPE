#pragma once

#include <LibraryInterfaces/IMove.hpp>
#include "IAttack.hpp"
#include <ECS/Components/Components.hpp>
#include "ECS/Components/Stats.hpp"

#include <Resources.hpp>

class BombAttack : public IAttack
{
  private:
    int _beforeExplosion;
    GameEngine::GameManagers &_gameManagers;
    ECS::Manager &_ecs;
    EventManager::Manager &_event;
    LibLoader &_loader;
    MapEngine   &_mapEngine;

    ECS::Entity _ownerEntity;

    std::string _TEXTURE = "bomb_texture";
    std::string _MOVE = "StraightMove";


    int _baseDamage = 0;
    ECS::Entity _entity;

    std::vector<ECS::Entity> _attacks;

    std::shared_ptr<IMove> _move;

    std::string _EXPLOSION_NAME = "bomb_explosion";

    std::string _spriteName;
    std::string _bombAnimationName;

    void generateChilds(std::string);

  public:
    BombAttack(GameEngine::GameManagers &gameManagers, MapEngine &mapEngine, ECS::Entity owner);
    ~BombAttack() override;
    void update() override;
    ECS::Entity getID() const override;
    void move();
};

#ifdef WIN32
extern "C"
{
	char const  __declspec(dllexport) *getName()
	{
		return "BombAttack";
	}

	IAttack  __declspec(dllexport) *getSymbol(GameEngine::GameManagers &gameManagers, MapEngine &mapEngine, ECS::Entity parent)
	{
		return new BombAttack(gameManagers, mapEngine, parent);
	}
}
#else

extern "C" char const * getName()
{
  return "BombAttack";
}

extern "C" IAttack *getSymbol(GameEngine::GameManagers &gameManagers, MapEngine &mapEngine, ECS::Entity parent)
{
  return new BombAttack(gameManagers, mapEngine, parent);
}

#endif