#pragma once

#include "IMove.hpp"

class SinusoideMove : public IMove
{
  private:
    GameEngine::GameManagers &_gameManagers;
    ECS::Manager &_ecs;
    EventManager::Manager &_event;
    LibLoader &_loader;

    ECS::Entity _owner;

  public:
    SinusoideMove(GameEngine::GameManagers &gameManagers, ECS::Entity entity);
    ~SinusoideMove() override;
    void update() override;
};


#if WIN32
extern "C" std::string __declspec(dllexport) __stdcall getName()
{
  return "SinusoideMove";
}

extern "C" IMove __declspec(dllexport) __stdcall *getSymbol(GameEngine::GameManagers &gameManagers, ECS::Entity parent)
{
  return new SinusoideMove(gameManagers, parent);
}

#else

extern "C" std::string getName()
{
  return "SinusoideMove";
}

extern "C" IMove *getSymbol(GameEngine::GameManagers &gameManagers, ECS::Entity parent)
{
  return new SinusoideMove(gameManagers, parent);
}

#endif
