/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-02-15T00:18:51+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-18T13:46:53+01:00
 */


#pragma once

#include  "IEntityObject.hpp"

#include  "GameManagers.hpp"
#include  "ECS/Components/Components.hpp"
#include  "ECS/Components/CommonComponents.hpp"

#include  <vector>
#include  <memory>

class MapEngine
{
public:
  explicit MapEngine(GameEngine::GameManagers &gameManagers);

  ~MapEngine() = default;

  template<typename C>
  void  addObject(ECS::Entity e, std::shared_ptr<C> object)
  {
    _objects.emplace(e, object);
  }

  void  addParallax(const std::string &layer, float speedLayer, bool flipVerticaly);
  void  clearParallax();

  void  updateObjects(void);
  void  deleteObject(ECS::Entity entity);

private:
  GameEngine::GameManagers  _gameManagers;
  std::map<ECS::Entity, std::shared_ptr<IEntityObject>> _objects;
  std::vector<ECS::Entity> _parallaxItems;
};
