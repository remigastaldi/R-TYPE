/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-13T02:28:43+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-13T03:26:33+01:00
 */


#pragma once

#include <ECS/Entity.hpp>
#include <ECS/Component/Component.hpp>

#include <map>
#include <set>

namespace ECS
{
  class Store
  {
  public:
    Store();

    bool has(Entity e);
    Component *get(Entity e);
    bool add(Entity e, Component *c);
    bool remove(Entity e);
    std::set<Entity> getEntities() const;

  private:
    std::map<Entity, Component *> _store;
  };
}
