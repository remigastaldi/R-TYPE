#pragma once

#include <LibraryInterfaces/IMob.hpp>
#include "IMap.hpp"
#include "Maps/ILevels.hpp"

class KirbyMap : public IMap
{
  private:
    std::pair<int, int> _neededLevel = std::make_pair(0, 5);

    EventManager::EventListener _listener;
    EventManager::EventListener _listenerOutOfSpace;

    int _wave = 0;

    ECS::Manager &_ecs;
    EventManager::Manager &_event;
    LibLoader &_loader;

    std::vector<std::shared_ptr<ILevels>> _levels;

    bool _isEnd = false;

  public:
    KirbyMap(ECS::Manager &ecs, EventManager::Manager &event, LibLoader &loader);
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

extern "C" IMap  __declspec(dllexport) __stdcall *getSymbol(ECS::Manager &ecs, EventManager::Manager &event, LibLoader &loader)
{
  return new KirbyMap(ecs, event, loader);
}

#else

extern "C" std::string getName()
{
  return "KirbyMap";
}

extern "C" IMap *getSymbol(ECS::Manager &ecs, EventManager::Manager &event, LibLoader &loader)
{
  return new KirbyMap(ecs, event, loader);
}

#endif