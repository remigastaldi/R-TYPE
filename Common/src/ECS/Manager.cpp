/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-13T01:04:05+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-16T19:46:26+01:00
 */


#include  "ECS/Manager.hpp"

namespace ECS
{
  Manager::Manager()
    : _next(1),
    _entities(),
    _systems(),
    _stores()
  {}

  Manager::~Manager()
  {
    // for (auto store : _stores)
    // {
    //   // TODO: delete content of store
    //   // delete store.second;
    // }
  }

  Entity Manager::createEntity()
  {
    Entity e = _next++;
    assert(e != INVALID_ENTITY);
    auto ret = _entities.emplace(e, std::set<ComponentType>());
    assert(ret.second);
    return e;
  }

  bool Manager::destroyEntity(Entity e)
  {
    auto count = _entities.erase(e);
    return (count > 0);
  }

  std::set<Entity> Manager::getEntities() const
  {
    std::set<Entity> ret;

    for (auto entity : _entities)
    {
      ret.insert(entity.first);
    }

    return (ret);
  }

  std::shared_ptr<Store> Manager::getStore(ComponentType ct)
  {
    auto it = _stores.find(ct);
    if (it == _stores.end())
      return (nullptr);

    return (std::shared_ptr<Store>(it->second));
    // return it == _stores.end() ? nullptr : it->second;
  }

  void Manager::initSystems()
  {
    std::sort(_systems.begin(), _systems.end(), [](const std::shared_ptr<System>& lhs, const std::shared_ptr<System>& rhs)
    {
      return lhs->getPriority() < rhs->getPriority();
    });

    for (auto& sys : _systems)
    {
      sys->init();
    }
  }

  void Manager::updateSystems(float delta)
  {
    for (auto& sys : _systems)
    {
      sys->preUpdate(delta);
    }

    for (auto& sys : _systems)
    {
      sys->update(delta);
    }

    for (auto& sys : _systems)
    {
      sys->postUpdate(delta);
    }
  }

  bool Manager::createStoreFor(ComponentType ct)
  {
    auto ret = _stores.insert(std::make_pair(ct, new Store));
    return ret.second;
  }

  std::shared_ptr<Component> Manager::getComponent(Entity e, ComponentType ct)
  {
    if (e == INVALID_ENTITY || ct == INVALID_COMPONENT)
    {
      return nullptr;
    }

    std::shared_ptr<Store> store(getStore(ct));

    if (store == nullptr)
    {
      return nullptr;
    }

    return store->get(e);
  }

  bool Manager::addComponent(Entity e, ComponentType ct, std::shared_ptr<Component> c)
  {
    if (e == INVALID_ENTITY || ct == INVALID_COMPONENT)
    {
      return false;
    }

    std::shared_ptr<Store> store(getStore(ct));

    if (store == nullptr)
    {
      return false;
    }

    auto it = _entities.find(e);

    if (it == _entities.end())
    {
      return false;
    }

    it->second.insert(ct);
    return store->add(e, c);
  }

  std::shared_ptr<Component> Manager::extractComponent(Entity e, ComponentType ct)
  {
    if (e == INVALID_ENTITY || ct == INVALID_COMPONENT)
    {
      return nullptr;
    }

    std::shared_ptr<Store> store(getStore(ct));

    if (store == nullptr)
    {
      return nullptr;
    }

    auto it = _entities.find(e);
    if (it == _entities.end())
    {
      return nullptr;
    }
    it->second.erase(ct);

    std::shared_ptr<Component> c(store->get(e));
    store->remove(e);
    return c;
  }

  int Manager::subscribeEntityToSystems(Entity e, std::set<ComponentType> components)
  {
    if (e == INVALID_ENTITY)
    {
      return 0;
    }

    int n = 0;

    for (auto& sys : _systems)
    {
      const std::set<ComponentType> needed = sys->getNeededComponents();
      if (components.size() > 0 && std::includes(components.begin(), components.end(), needed.begin(), needed.end()))
      {
        sys->addEntity(e);
        n++;
      }
      else
      {
        sys->removeEntity(e);
      }
    }

    return n;
  }

  int Manager::subscribeEntityToSystems(Entity e)
  {
    auto it = _entities.find(e);

    if (it == _entities.end())
    {
      return 0;
    }

    return subscribeEntityToSystems(e, it->second);
  }


  bool Manager::addSystem(std::shared_ptr<System> sys)
  {
    if (sys)
    {
      _systems.push_back(sys);
    }

    return true;
  }
}
