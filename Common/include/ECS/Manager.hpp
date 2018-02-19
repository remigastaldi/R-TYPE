/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-13T01:04:20+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-19T16:38:56+01:00
 */


#pragma once

#include  "ECS/Store.hpp"
#include  "ECS/System.hpp"

#include  "ECS/Components/CommonComponents.hpp"

#include <AlfredBase/Utils/Counter.hpp>

#include  <map>
#include  <memory>
#include  <set>
#include  <string>
#include  <type_traits>
#include  <vector>
#include  <cassert>
#include  <algorithm>
#include  <type_traits>
#include <Logger/Logger.hpp>

namespace ECS
{
  class Mouvement;
  class Manager {


    public:
      template <typename T>
      inline unsigned GetTypeID()
      {
        return static_cast<size_t>(typeid(T).hash_code());
      }

      /**
       * @brief Class
       */
  public:
    Manager();

    ~Manager();

    Entity createEntity();
    bool   destroyEntity(Entity e);
    std::set<Entity> getEntities() const;
    std::set<ComponentType> getEntityComponents(Entity) const;

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
      return createStoreFor(GetTypeID<C>());
    }

    std::shared_ptr<Component> getComponent(Entity e, ComponentType ct);

    template<typename C>
    std::shared_ptr<C> getComponent(Entity e) {
      static_assert(std::is_base_of<Component, C>::value, "C must be a Component");
      return std::static_pointer_cast<C>(getComponent(e, GetTypeID<C>()));
    }


      template <typename C>
    bool addComponent(Entity e, std::shared_ptr<Component> c)
      {
        size_t comptype = GetTypeID<C>();

        if (e == INVALID_ENTITY)
        {
          return false;
        }

        std::shared_ptr<Store> store(getStore(comptype));

        if (store == nullptr)
        {
          return false;
        }

        auto it = _entities.find(e);

        if (it == _entities.end())
        {
          return false;
        }

        it->second.insert(comptype);
        return store->add(e, c);
      };

    template<typename C>
    bool addComponent(Entity e, C c) {
      static_assert(std::is_base_of<Component, C>::value, "C must be a Component");
      return addComponent<C>(e, std::static_pointer_cast<Component>(std::make_shared<C>(c)));
    }

    std::shared_ptr<Component> extractComponent(Entity e, ComponentType ct);

    template<typename C>
    std::shared_ptr<C> extractComponent(Entity e) {
      static_assert(std::is_base_of<Component, C>::value, "C must be a Component");
      return std::static_pointer_cast<C>(extractComponent(e, GetTypeID<C>()));
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
