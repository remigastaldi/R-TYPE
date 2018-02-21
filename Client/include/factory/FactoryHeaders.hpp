#pragma once

namespace GameEngine
{
  struct GameManagers;
}

class MapEngine;

class IAttack;

class IMap;

class IMob;

class IMove;

class IPart;

class IPowerUp;

class IRessources;

class IScene;

class IShipBluprint;

class LibLoader;

#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
#include "FindOS.hpp"
#include <AlfredBase/Utils/NonCopyable.hpp>
#include <unordered_map>
#include "DynamicLibrary/DynamicLibraryTypes.hpp"
#include "Logger/Logger.hpp"
#include "ECS/Manager.hpp"
#include "ECS/Component.hpp"
#include <type_traits>
#include <GameManagers.hpp>

namespace EventManager
{
  class Manager;
}

#ifdef WIN32

typedef char const * (*getNameOfLib)();

typedef IAttack *(*getAttackSymbol)(GameEngine::GameManagers &gameManagers, MapEngine &mapEngine, ECS::Entity);
typedef IMap *(*getMapSymbol)(GameEngine::GameManagers &gameManagers);
typedef IMob *(*getMobSymbol)(GameEngine::GameManagers &gameManagers, MapEngine &mapEngine, ECS::Components::Position);
typedef IMove *(*getMoveSymbol)(GameEngine::GameManagers &gameManagers, ECS::Entity, int direction, int speed);
typedef IPart *(*getPartSymbol)();
typedef IPowerUp *(*getPowerUpSymbol)();
typedef IRessources *(*getRessourceSymbol)(GameEngine::GameManagers &gameManagers);
typedef IScene *(*getSceneSymbol)();
typedef IShipBluprint *(*getShipBlueprintSymbol)();

#else

typedef char const *(*getNameOfLib)();

typedef IAttack *(*getAttackSymbol)(GameEngine::GameManagers &gameManagers, MapEngine &mapEngine, ECS::Entity);
typedef IMap *(*getMapSymbol)(GameEngine::GameManagers &gameManagers);
typedef IMob *(*getMobSymbol)(GameEngine::GameManagers &gameManagers, MapEngine &mapEngine, ECS::Components::Position);
typedef IMove *(*getMoveSymbol)(GameEngine::GameManagers &gameManagers, ECS::Entity, int direction, int speed);
typedef IPart *(*getPartSymbol)();
typedef IPowerUp *(*getPowerUpSymbol)();
typedef void (*getRessourceSymbol)(GameEngine::GameManagers &);
typedef IScene *(*getSceneSymbol)();
typedef IShipBluprint *(*getShipBlueprintSymbol)();

#endif
