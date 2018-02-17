/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-02-16T15:34:19+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-16T15:45:48+01:00
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

    size_t speed = 2;

    GameEngine::GameManagers &_gameManagers;
    ECS::Manager &_ecs;
    EventManager::Manager &_event;
    LibLoader &_loader;
    ECS::Entity _owner;

  public:
    StraightMove(GameEngine::GameManagers &gameManagers, ECS::Entity entity);
    ~StraightMove() override;
    void update() override;
};

extern "C" char const * getName()
{
  return "StraightMove";
}

extern "C" IMove *getSymbol(GameEngine::GameManagers &gameManagers, ECS::Entity parent)
{
  return new StraightMove(gameManagers, parent);
}
