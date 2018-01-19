/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-13T00:47:26+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-18T02:23:16+01:00
 */


#include  "ECS/System.hpp"

namespace ECS
{
  System::~System()
  {}

  void System::init()
  {}

  bool System::addEntity(Entity e)
  {
    auto ret = _entities.insert(e);
    // std::pair<Entity, bool> ret = _entities.insert(e);
    return (ret.second);
  }

  bool System::removeEntity(Entity e)
  {
    size_t ret = _entities.erase(e);
    return ret > 0;
  }

  void System::preUpdate(float delta)
  {
    (void)delta;
  }

  void System::update(float delta)
  {
    auto copy = getEntities();
    for (Entity e : copy)
    {
      updateEntity(delta, e);
    }
  }

  void System::updateEntity(float delta, Entity e)
  {
    (void) delta;
    (void) e;
  }

  void System::postUpdate(float delta)
  {
    (void)delta;
  }

  int System::getPriority() const
  {
    return (_priority);
  }

  std::set<ComponentType> System::getNeededComponents() const
  {
    return (_needed);
  }

  ECS::Manager &System::getManager()
  {
    return (_manager);
  }
}
