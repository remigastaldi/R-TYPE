/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-13T01:04:20+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-21T00:46:07+01:00
 */


#pragma once

#include  "ECS/Store.hpp"
#include  "ECS/System.hpp"

#include  "ECS/Components/CommonComponents.hpp"

#include  <map>
#include  <memory>
#include  <set>
#include  <string>
#include  <type_traits>
#include  <vector>
#include  <cassert>
#include  <algorithm>
#include  <type_traits>

namespace ECS
{
  class Mouvement;
  class Manager {
  public:
    Manager();

    ~Manager();

    Entity createEntity();
    bool   destroyEntity(Entity e);
    std::set<Entity> getEntities() const;

    std::shared_ptr<Store> getStore(ComponentType ct);

    void  initSystems();
    void  updateSystems(float delta);
    void  updateSystemsRange(float delta, int from, int to);


    int updateEntityToSystems(Entity e, std::set<ComponentType> components);
    int updateEntityToSystems(Entity e);


    bool  createStoreFor(ComponentType ct);

    template<typename C>
    bool createStoreFor() {
      static_assert(std::is_base_of<Component, C>::value, "C must be a Component");
      static_assert(C::Type != INVALID_COMPONENT, "C must define its type");
      return createStoreFor(C::Type);
    }

    std::shared_ptr<Component> getComponent(Entity e, ComponentType ct);

    template<typename C>
    std::shared_ptr<C> getComponent(Entity e) {
      static_assert(std::is_base_of<C, C>::value, "C must be a Component");
      static_assert(C::Type != INVALID_COMPONENT, "C must define its type");
      return std::static_pointer_cast<C>(getComponent(e, C::Type));
    }


    bool addComponent(Entity e, ComponentType ct, std::shared_ptr<Component> c);

    template<typename C>
    bool addComponent(Entity e, C c) {
      static_assert(std::is_base_of<C, C>::value, "C must be a Component");
      static_assert(C::Type != INVALID_COMPONENT, "C must define its type");
      return addComponent(e, C::Type, std::static_pointer_cast<Component>(std::make_shared<C>(c)));
    }

    std::shared_ptr<Component> extractComponent(Entity e, ComponentType ct);

    template<typename C>
    std::shared_ptr<C> extractComponent(Entity e) {
      static_assert(std::is_base_of<C, C>::value, "C must be a Component");
      static_assert(C::Type != INVALID_COMPONENT, "C must define its type");
      return std::static_pointer_cast<C>(extractComponent(e, C::Type));
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
    std::map<ComponentType, std::shared_ptr<Store>> _stores;
  };
}
