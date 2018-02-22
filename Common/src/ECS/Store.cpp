/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-13T03:22:48+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-14T22:00:42+01:00
 */


#include  "ECS/Store.hpp"

namespace ECS
{
  Store::Store()
    : _store()
  {}

  bool Store::has(Entity e)
  {
    auto it = _store.find(e);
    return it != _store.end();
  }

  std::shared_ptr<Component> Store::get(Entity e)
  {
    auto it = _store.find(e);

    if (it == _store.end())
      return (nullptr);

    return (it->second);
  }

  bool Store::add(Entity e, std::shared_ptr<Component> c)
  {
    auto ret = _store.insert(std::make_pair(e, c));
    return ret.second;
  }

  bool Store::remove(Entity e)
  {
    auto count = _store.erase(e);
    return count > 0;
  }

  std::set<Entity> Store::getEntities() const
  {
    std::set<Entity> ret;

    for (auto elt : _store)
    {
      ret.insert(elt.first);
    }

    return ret;
  }
}
