#pragma once

#include <LibraryInterfaces/IMove.hpp>

class UpAndDownMove : public IMove
{
  private:
    ECS::Manager &_ecs;
    EventManager::Manager &_event;
    LibLoader &_loader;

    ECS::Entity _owner;

    int _lastTickUpdate;
    int _needTickToUpdate = 100;

  public:
    UpAndDownMove(ECS::Manager &ecs, EventManager::Manager &event, LibLoader &loader, ECS::Entity entity);
    ~UpAndDownMove() override;
    void update() override;
};

extern "C" std::string getName()
{
  return "UpAndDownMove";
}

extern "C" IMove *getSymbol(ECS::Manager &ecs, EventManager::Manager &event, LibLoader &loader, ECS::Entity parent)
{
  return new UpAndDownMove(ecs, event, loader, parent);
}