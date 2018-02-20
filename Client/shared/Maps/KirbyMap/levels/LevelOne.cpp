/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-02-15T16:16:24+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-20T22:42:43+01:00
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
  // if (_nbMobSpawn <= 0) {
  //   if (_mobs.empty())
  //     _isEnd = true;
  //   return;
  // }

  if (_timeLeft > -10)
    _timeLeft -= 1;

  if (_timeLeft < 0) {
    _timeLeft = _timeBetweenMobSpawn;
    _nbMobSpawn -= 1;

    //Spawn a mob
    LOG_INFO << "Spawning a mob " << _nbMobSpawn << std::endl;


    std::shared_ptr<IMob> tmp(_loader.mob.get("Metallos")(_gameManagers, _mapEngine, ECS::Components::Position(1800, 900)));
    _mapEngine.addObject<IMob>(tmp->getID(), tmp);
    // _mobs[tmp->getID()] = tmp;
  }

  //Update mobs
  // for (auto &it : _mobs)
  //   it.second->update();
  _mapEngine.updateObjects();
}

LevelOne::LevelOne(GameEngine::GameManagers &gameManagers, MapEngine &mapEngine) :
  ILevels(gameManagers, mapEngine),
  _gameManagers(gameManagers),
  _ecs(gameManagers.ecs),
  _event(gameManagers.event),
  _loader(gameManagers.libLoader),
  _mapEngine(mapEngine),
  _mobs()
{
  LOG_INFO << "Loading Level One" << std::endl;
}

LevelOne::~LevelOne()
{
}

void LevelOne::unitOutOfSpace(ECS::Entity entity)
{
  _mapEngine.deleteObject(entity);
  // if (_mobs.find(entity) != _mobs.end()) {
  //   _mobs.erase(entity);
  //   LOG_SUCCESS << "Mob out of space deleted" << std::endl;
  //   return;
  // }
  //
  // for (auto &it : _mobs)
  //   it.second->unitOutOfSpace(entity);
}

void  LevelOne::unitDie(ECS::Entity entity)
{
  _mapEngine.deleteObject(entity);
}
