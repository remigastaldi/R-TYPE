/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-02-14T19:31:45+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-21T00:48:11+01:00
 */


#pragma once

#include  "IMap.hpp"

#include "LibraryInterfaces/IMob.hpp"
#include "MapEngine.hpp"
#include "Maps/ILevels.hpp"
#include "Ship.hpp"

class KirbyMap : public IMap
{
  private:
    std::pair<int, int> _neededLevel = std::make_pair(0, 5);

    std::unordered_map<std::string, EventManager::EventListener> _listeners;

    size_t _wave = 0;

    GameEngine::GameManagers &_gameManagers;
    ECS::Manager &_ecs;
    EventManager::Manager &_event;
    LibLoader &_loader;

    std::vector<std::shared_ptr<ILevels>> _levels;

    bool _isEnd = false;

    MapEngine   _mapEngine;

  public:
    explicit KirbyMap(GameEngine::GameManagers &gameManagers);
    ~KirbyMap();
    const std::pair<int, int> &getNeededLevel() const override;
    void update() override;
    bool isEnd() override;
};

#ifdef WIN32
extern "C"
{ 
	char const  __declspec(dllexport) *getName()
	{
		return "KirbyMap";
	}

	IMap  __declspec(dllexport) *getSymbol(GameEngine::GameManagers &gameManagers)
	{
		return new KirbyMap(gameManagers);
	}
}
#else

extern "C" char const * getName()
{
  return "KirbyMap";
}

extern "C" IMap *getSymbol(GameEngine::GameManagers &gameManagers)
{
  return new KirbyMap(gameManagers);
}

#endif
