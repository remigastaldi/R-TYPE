#pragma once

#include <LibraryInterfaces/IMove.hpp>
#include <ECS/Components/Components.hpp>


class StraightMove : public IMove
{
  private:
    std::string name = "StraightMove";
    ECS::Entity _entity;
    ECS::Entity _owner;

    size_t speed = 2;

    ECS::Manager &_ecs;
    EventManager::Manager &_event;

  public:
    StraightMove(ECS::Manager &ecs, EventManager::Manager &event);
    ~StraightMove() override;
    ECS::Entity getID() override;
    const std::string &getName() const override;
    void update(const float time) override;
    void giveOwnerEntity(ECS::Entity entity) override;
};