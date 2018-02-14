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

extern "C" std::string getName()
{
  return "StraightMove";
}

extern "C" IMove *getSymbol(GameEngine::GameManagers &gameManagers, ECS::Entity parent)
{
  return new StraightMove(gameManagers, parent);
}
