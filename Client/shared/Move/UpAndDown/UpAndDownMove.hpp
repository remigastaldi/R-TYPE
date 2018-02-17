/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-02-16T14:09:59+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-17T13:31:23+01:00
 */


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

#ifdef WIN32
extern "C" char const * __declspec(dllexport) __stdcall getName()
{
  return "UpAndDownMove";
}

extern "C" IMove __declspec(dllexport) __stdcall *getSymbol(GameEngine::GameManagers &gameManagers, ECS::Entity parent)
{
  return new UpAndDownMove(gameManagers, parent);
}

#else

extern "C" char const * getName()
{
  return "UpAndDownMove";
}

extern "C" IMove *getSymbol(GameEngine::GameManagers &gameManagers, ECS::Entity parent)
{
  return new UpAndDownMove(gameManagers, parent);
}

#endif
