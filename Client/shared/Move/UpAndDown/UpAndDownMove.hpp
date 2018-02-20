/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-02-16T14:09:59+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-19T14:49:58+01:00
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

    short _isForwarding = 0;

  public:
    UpAndDownMove(GameEngine::GameManagers &gameManagers, ECS::Entity entity, int direction, int speed);
    ~UpAndDownMove() override;

    void update() override;
    ECS::Entity getID(void) const override;
};

#ifdef WIN32
extern "C" char const * __declspec(dllexport) __stdcall getName()
{
  return "UpAndDownMove";
}

extern "C" IMove __declspec(dllexport) __stdcall *getSymbol(GameEngine::GameManagers &gameManagers, ECS::Entity parent, int direction, int speed)
{
  return new UpAndDownMove(gameManagers, parent, direction, speed);
}

#else

extern "C" char const * getName()
{
  return "UpAndDownMove";
}

extern "C" IMove *getSymbol(GameEngine::GameManagers &gameManagers, ECS::Entity parent, int direction, int speed)
{
  return new UpAndDownMove(gameManagers, parent, direction, speed);
}

#endif
