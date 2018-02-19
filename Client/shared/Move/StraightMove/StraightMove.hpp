/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-02-16T15:34:19+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-19T16:23:34+01:00
 */


#pragma once

#include <LibraryInterfaces/IMove.hpp>
#include <ECS/Components/Components.hpp>
#include <DynamicLibrary/LibLoader.hpp>

#include <GameManagers.hpp>

class StraightMove : public IMove
{
  private:
    std::string name = "StraightMove";

    GameEngine::GameManagers &_gameManagers;
    ECS::Manager &_ecs;
    EventManager::Manager &_event;
    LibLoader &_loader;
    ECS::Entity _owner;

  public:
    StraightMove(GameEngine::GameManagers &gameManagers, ECS::Entity entity, int direction, int speed);
    ~StraightMove();

    void update() override;
    ECS::Entity getID(void) const override;
};

#ifdef WIN32
extern "C" char const * __declspec(dllexport) __stdcall getName()
{
  return "StraightMove";
}

extern "C" IMove __declspec(dllexport) __stdcall *getSymbol(GameEngine::GameManagers &gameManagers, ECS::Entity parent, int direction, int speed)
{
  return new StraightMove(gameManagers, parent, direction, speed);
}

#else

extern "C" char const * getName()
{
  return "StraightMove";
}

extern "C" IMove *getSymbol(GameEngine::GameManagers &gameManagers, ECS::Entity parent, int direction, int speed)
{
  return new StraightMove(gameManagers, parent, direction, speed);
}

#endif
