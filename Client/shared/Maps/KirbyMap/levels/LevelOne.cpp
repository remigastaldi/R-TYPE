/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-02-15T16:16:24+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-24T19:54:08+01:00
 */


#include <ECS/Components/Stats.hpp>
#include "LevelOne.hpp"

const std::string &LevelOne::getName()
{
  return _name;
}

void LevelOne::enter()
{
  LOG_ERROR << "Je rentre dans le niveau un" << std::endl;
}

void LevelOne::exit()
{
  LOG_ERROR << "Bravo tu as fini le niveau un !" << std::endl;
}

bool LevelOne::isEnd()
{
  return _isEnd;
}

void LevelOne::update()
{
  if (_nbMobSpawn <= 0) {
    if (_ecs.getStore(_ecs.GetTypeID<ECS::Components::Ennemy>())->size() <= 0) {
      _isEnd = true;
      return;
    }
  }

  if (_timeLeft > -10)
    _timeLeft -= 1;

  if (_timeLeft < 0 && _nbMobSpawn > 0) {
    _timeLeft = _timeBetweenMobSpawn;
    _nbMobSpawn -= 2;

    std::shared_ptr<IMob> tmp(
      _loader.mob.get("Metallos")(_gameManagers, _mapEngine, ECS::Components::Position(1800, 900)));
    std::shared_ptr<IMob> tmp2(
      _loader.mob.get("Metallos")(_gameManagers, _mapEngine, ECS::Components::Position(1800, 400)));
    _mapEngine.addObject<IMob>(tmp->getID(), tmp);
    _mapEngine.addObject<IMob>(tmp2->getID(), tmp2);
  }

}

LevelOne::LevelOne(GameEngine::GameManagers &gameManagers, MapEngine &mapEngine) :
  ILevels(gameManagers, mapEngine),
  _gameManagers(gameManagers),
  _ecs(gameManagers.ecs),
  _event(gameManagers.event),
  _loader(gameManagers.libLoader),
  _mapEngine(mapEngine)
{
  LOG_INFO << "Loading Level One" << std::endl;
}

LevelOne::~LevelOne()
{
}

int LevelOne::unitOutOfSpace(ECS::Entity entity)
{
  if (_mapEngine.deleteObject(entity) == 0) {
    _ecs.destroyEntity(entity);
  }
  return 0;
}

void LevelOne::unitDie(ECS::Entity entity)
{
  _mapEngine.deleteObject(entity);
}
