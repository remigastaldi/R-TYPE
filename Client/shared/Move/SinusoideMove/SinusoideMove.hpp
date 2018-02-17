/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-02-16T15:34:14+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-17T13:31:19+01:00
 */


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


#ifdef WIN32
extern "C" char const * __declspec(dllexport) __stdcall getName()
{
  return "SinusoideMove";
}

extern "C" IMove __declspec(dllexport) __stdcall *getSymbol(GameEngine::GameManagers &gameManagers, ECS::Entity parent)
{
  return new SinusoideMove(gameManagers, parent);
}

#else

extern "C" char const * getName()
{
  return "SinusoideMove";
}

extern "C" IMove *getSymbol(GameEngine::GameManagers &gameManagers, ECS::Entity parent)
{
  return new SinusoideMove(gameManagers, parent);
}

#endif
