#pragma once

#include <LibraryInterfaces/IMove.hpp>

class UpAndDownMove : public IMove
{
  private:
    GameEngine::GameManagers &_gameManagers;
    ECS::Manager &_ecs;
    EventManager::Manager &_event;
    LibLoader &_loader;

    ECS::Entity _owner;

  public:
    UpAndDownMove(GameEngine::GameManagers &gameManagers, ECS::Entity entity);
    ~UpAndDownMove() override;
    void update() override;
};

#if WIN32
extern "C" std::string __declspec(dllexport) __stdcall getName()
{
  return "UpAndDownMove";
}

extern "C" IMove __declspec(dllexport) __stdcall *getSymbol(GameEngine::GameManagers &gameManagers, ECS::Entity parent)
{
  return new UpAndDownMove(gameManagers, parent);
}

#else

extern "C" std::string getName()
{
  return "UpAndDownMove";
}

extern "C" IMove *getSymbol(GameEngine::GameManagers &gameManagers, ECS::Entity parent)
{
  return new UpAndDownMove(gameManagers, parent);
}

#endif
