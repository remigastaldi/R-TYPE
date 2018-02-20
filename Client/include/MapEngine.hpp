/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-02-15T00:18:51+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-19T18:21:10+01:00
 */


#pragma once

#include  "IEntityObject.hpp"

#include  "GameManagers.hpp"
#include  "ECS/Components/Components.hpp"
#include  "ECS/Components/CommonComponents.hpp"

#include  <vector>
#include  <memory>
#include "IMove.hpp"

class MapEngine
{
public:
  explicit MapEngine(GameEngine::GameManagers &gameManagers);

  ~MapEngine() = default;

  template<typename C>
  void  addObject(ECS::Entity e, std::shared_ptr<C> object)
  {
    auto it = _objects.find(e);
    if (it != _objects.end())
      {
        it->second.emplace_back(object);
      }
    else
    {
      std::vector<std::shared_ptr<IEntityObject>> objects;
      objects.emplace_back(object);
      _objects.emplace(e, objects);
    }
  }

  void  addParallax(const std::string &layer, float speedLayer, bool flipVerticaly);
  void  clearParallax();

  void  updateObjects(void);

  void  deleteObject(ECS::Entity entity);

  template<typename C>
  void  deleteObjectFromEntity(ECS::Entity entity)
  {
    auto it = _objects[entity].cbegin();
    while (it != _objects[entity].cend())
    {
      std::shared_ptr<C> test = std::dynamic_pointer_cast<C>(*it);
      if (test.get() != nullptr)
        _objects[entity].erase(it);
      it = std::next(it);
    }
  }

private:
  GameEngine::GameManagers  _gameManagers;
  std::map<ECS::Entity, std::vector<std::shared_ptr<IEntityObject>>> _objects;
  std::vector<ECS::Entity> _parallaxItems;
};
