/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-02-14T19:31:45+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-15T00:36:47+01:00
 */


#pragma once

#include <LibraryInterfaces/IMob.hpp>
#include "Maps/MapEngine.hpp"
#include "Maps/ILevels.hpp"

class KirbyMap : public MapEngine
{
  private:
    std::pair<int, int> _neededLevel = std::make_pair(0, 5);

    EventManager::EventListener _listener;
    EventManager::EventListener _listenerOutOfSpace;

    int _wave = 0;

    GameEngine::GameManagers &_gameManagers;
    ECS::Manager &_ecs;
    EventManager::Manager &_event;
    LibLoader &_loader;

    std::vector<std::shared_ptr<ILevels>> _levels;

    bool _isEnd = false;

  public:
    KirbyMap(GameEngine::GameManagers &gameManagers);
    ~KirbyMap() override;
    const std::pair<int, int> &getNeededLevel() const override;
    void update() override;
    bool isEnd() override;
};

#if WIN32
extern "C" std::string __declspec(dllexport) __stdcall getName()
{
  return "KirbyMap";
}

extern "C" IMap  __declspec(dllexport) __stdcall *getSymbol(GameEngine::GameManagers &gameManagers)
{
  return new KirbyMap(gameManagers);
}

#else

extern "C" std::string getName()
{
  return "KirbyMap";
}

extern "C" IMap *getSymbol(GameEngine::GameManagers &gameManagers)
{
  return new KirbyMap(gameManagers);
}

#endif
