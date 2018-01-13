/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-13T00:16:14+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-13T03:44:07+01:00
 */


#pragma once

#include <ECS/Entity.hpp>
#include <ECS/Component/Component.hpp>

#include <set>
#include <memory>

namespace ECS
{
  class Manager;
  class System
  {
  public:
    System(int priority, std::set<ComponentType> &needed, std::weak_ptr<Manager> manager)
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

    std::weak_ptr<Manager> getManager();

  private:
    const int _priority;
    const std::set<ComponentType> _needed;

    // Manager * const _manager;
    std::weak_ptr<Manager> _manager;
    std::set<Entity> _entities;
  };
}
