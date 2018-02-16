/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-02-15T00:18:51+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-15T22:44:34+01:00
 */


#pragma once

#include  "IMap.hpp"
#include  "GameManagers.hpp"
#include  "ECS/Components/Components.hpp"
#include  "ECS/Components/CommonComponents.hpp"

#include  <vector>
#include  <memory>

class MapEngine : public IMap
{
  class IObject
  {
    IObject();
  };
  template<class T>
  class Object : public IObject
  {
    Object();
  };

public:
  explicit MapEngine(GameEngine::GameManagers &gameManagers);

  ~MapEngine() = default;

  template<typename C>
  void  addObject(C object)
  {
    _objects.emplace_back(object);
  }

  void  addParallax(const std::string &layer, float speedLayer, bool flipVerticaly);
  void  clearParallax();

private:
  GameEngine::GameManagers  _gameManagers;
  std::vector<std::shared_ptr<IObject>> _objects;
  std::vector<ECS::Entity> _parallaxItems;
};
