#pragma once

#include <LibraryInterfaces/IMove.hpp>

class UpAndDownMove : public IMove
{
  private:
    ECS::Manager &_ecs;
    EventManager::Manager &_event;
    LibLoader &_loader;

    ECS::Entity _owner;

  public:
    UpAndDownMove(ECS::Manager &ecs, EventManager::Manager &event, LibLoader &loader, ECS::Entity entity);
    ~UpAndDownMove() override;
    void update() override;
};

#if WIN32
extern "C" std::string __declspec(dllexport) __stdcall getName()
{
  return "UpAndDownMove";
}

extern "C" IMove __declspec(dllexport) __stdcall *getSymbol(ECS::Manager &ecs, EventManager::Manager &event, LibLoader &loader, ECS::Entity parent)
{
  return new UpAndDownMove(ecs, event, loader, parent);
}

#else

extern "C" std::string getName()
{
  return "UpAndDownMove";
}

extern "C" IMove *getSymbol(ECS::Manager &ecs, EventManager::Manager &event, LibLoader &loader, ECS::Entity parent)
{
  return new UpAndDownMove(ecs, event, loader, parent);
}

#endif