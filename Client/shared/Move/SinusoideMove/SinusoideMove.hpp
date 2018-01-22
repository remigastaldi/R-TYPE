#pragma once

#include "IMove.hpp"

class SinusoideMove : public IMove
{
  private:
    ECS::Manager &_ecs;
    EventManager::Manager &_event;
    LibLoader &_loader;

    ECS::Entity _owner;

  public:
    SinusoideMove(ECS::Manager &ecs, EventManager::Manager &event, LibLoader &loader, ECS::Entity entity);
    ~SinusoideMove() override;
    void update() override;
};


#if WIN32
extern "C" std::string __declspec(dllexport) __stdcall getName()
{
  return "SinusoideMove";
}

extern "C" IMove __declspec(dllexport) __stdcall *getSymbol(ECS::Manager &ecs, EventManager::Manager &event, LibLoader &loader, ECS::Entity parent)
{
  return new SinusoideMove(ecs, event, loader, parent);
}

#else

extern "C" std::string getName()
{
  return "SinusoideMove";
}

extern "C" IMove *getSymbol(ECS::Manager &ecs, EventManager::Manager &event, LibLoader &loader, ECS::Entity parent)
{
  return new SinusoideMove(ecs, event, loader, parent);
}

#endif