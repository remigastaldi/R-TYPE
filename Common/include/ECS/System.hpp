/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-13T00:16:14+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-14T01:30:13+01:00
 */


#pragma once

#include "ECS/Entity.hpp"
#include "ECS/Component.hpp"

#include <set>
#include <memory>
#include <experimental/memory>
#include <type_traits>

namespace std
{
  using namespace std::experimental;
}

namespace ECS
{
  class Manager;
  class System
  {
  public:
    System(int priority, std::set<ComponentType> needed, std::observer_ptr<ECS::Manager> &manager)
      : _priority(priority), _needed(needed), _manager(manager), _entities()
    {}

    virtual ~System();

    virtual void init();


    virtual bool addEntity(Entity e);
    virtual bool removeEntity(Entity e);
    virtual void updateEntity(float delta, Entity e);

    virtual void preUpdate(float delta);
    virtual void update(float delta);
    virtual void postUpdate(float delta);

    const std::set<Entity> getEntities() const { return _entities; }

    int getPriority() const;
    std::set<ComponentType> getNeededComponents() const;

    std::observer_ptr<ECS::Manager> &getManager();

  private:
    const int _priority;
    const std::set<ComponentType> _needed;

    // Manager * const _manager;
    std::observer_ptr<ECS::Manager> _manager;
    std::set<Entity> _entities;
  };
}
