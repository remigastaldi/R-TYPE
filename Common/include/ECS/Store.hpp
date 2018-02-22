/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-13T02:28:43+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-14T22:00:19+01:00
 */


#pragma once

#include "ECS/Entity.hpp"
#include "ECS/Component.hpp"

#include <map>
#include <set>
#include <memory>

namespace ECS
{
  class Store
  {
  public:
    Store();

    bool has(Entity e);
    std::shared_ptr<Component> get(Entity e);
    bool add(Entity e, std::shared_ptr<Component> c);
    bool remove(Entity e);
    std::set<Entity> getEntities() const;
      int size() {
        return _store.size();
      }

  private:
    std::map<Entity, std::shared_ptr<Component>> _store;
  };
}
