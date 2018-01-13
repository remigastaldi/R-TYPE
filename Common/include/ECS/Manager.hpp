/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-13T01:04:20+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-13T03:19:01+01:00
 */


#pragma once

#include <ECS/Store.hpp>
#include <ECS/System/System.hpp>

#include <map>
#include <memory>
#include <set>
#include <string>
#include <type_traits>
#include <vector>
#include <cassert>
#include <algorithm>

namespace ECS
{
  class Manager {
  public:
    Manager();

    ~Manager();

    Entity createEntity();
    bool   destroyEntity(Entity e);
    std::set<Entity> getEntities() const;

    Store *getStore(ComponentType ct);

    void initSystems();
    void updateSystems(float delta);

    int subscribeEntityToSystems(Entity e, std::set<ComponentType> components);
    int subscribeEntityToSystems(Entity e);


    bool  createStoreFor(ComponentType ct);

    template<typename C>
    bool createStoreFor() {
      static_assert(std::is_base_of<Component, C>::value, "C must be a Component");
      static_assert(C::type != INVALID_COMPONENT, "C must define its type");
      return createStoreFor(C::type);
    }


    Component *getComponent(Entity e, ComponentType ct);

    template<typename C>
    C *getComponent(Entity e) {
      static_assert(std::is_base_of<Component, C>::value, "C must be a Component");
      static_assert(C::type != INVALID_COMPONENT, "C must define its type");
      return static_cast<C*>(getComponent(e, C::type));
    }


    bool addComponent(Entity e, ComponentType ct, Component *c);

    template<typename C>
    bool addComponent(Entity e, C *c) {
      static_assert(std::is_base_of<Component, C>::value, "C must be a Component");
      static_assert(C::type != INVALID_COMPONENT, "C must define its type");
      return addComponent(e, C::type, c);
    }


    Component *extractComponent(Entity e, ComponentType ct);

    template<typename C>
    C *extractComponent(Entity e) {
      static_assert(std::is_base_of<Component, C>::value, "C must be a Component");
      static_assert(C::type != INVALID_COMPONENT, "C must define its type");
      return static_cast<C*>(extractComponent(e, C::type));
    }


    bool addSystem(std::shared_ptr<System> sys);

    template<typename S, typename ... Args>
    bool addSystem(Args&&... args) {
      static_assert(std::is_base_of<System, S>::value, "S must be a System");
      return addSystem(std::make_shared<S>(std::forward<Args>(args)...));
    }

  private:
    Entity _next;

    std::map<Entity, std::set<ComponentType>> _entities;
    std::vector<std::shared_ptr<System>> _systems;
    std::map<ComponentType, Store *> _stores;
  };
}
