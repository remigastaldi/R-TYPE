#pragma once

#include <LibraryInterfaces/IMove.hpp>
#include <ECS/Components/Components.hpp>
#include <DynamicLibrary/LibLoader.hpp>

class StraightMove : public IMove
{
  private:
    std::string name = "StraightMove";

    size_t speed = 2;

    ECS::Manager &_ecs;
    EventManager::Manager &_event;
    LibLoader &_loader;
    ECS::Entity _owner;

  public:
    StraightMove(ECS::Manager &ecs, EventManager::Manager &event, LibLoader &loader, ECS::Entity entity);
    ~StraightMove() override;
    void update() override;
};

extern "C" std::string getName()
{
  return "StraightMove";
}

extern "C" IMove *getSymbol(ECS::Manager &ecs, EventManager::Manager &event, LibLoader &loader, ECS::Entity parent)
{
  return new StraightMove(ecs, event, loader, parent);
}