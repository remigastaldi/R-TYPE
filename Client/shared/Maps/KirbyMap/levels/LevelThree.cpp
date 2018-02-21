#include <ECS/Components/Stats.hpp>
#include "LevelThree.hpp"

const std::string &LevelThree::getName()
{
  return _name;
}

void LevelThree::enter()
{
  LOG_ERROR << "Je rentre dans le niveau un" << std::endl;
}

void LevelThree::exit()
{
  LOG_ERROR << "Bravo tu as fini le niveau un !" << std::endl;
}

bool LevelThree::isEnd()
{
  return _isEnd;
}

void LevelThree::update()
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
      _loader.mob.get("Bomber")(_gameManagers, _mapEngine, ECS::Components::Position(1800, 500)));
    _mapEngine.addObject<IMob>(tmp->getID(), tmp);
  }

  _mapEngine.updateObjects();
}

LevelThree::LevelThree(GameEngine::GameManagers &gameManagers, MapEngine &mapEngine) :
  ILevels(gameManagers, mapEngine),
  _gameManagers(gameManagers),
  _ecs(gameManagers.ecs),
  _event(gameManagers.event),
  _loader(gameManagers.libLoader),
  _mapEngine(mapEngine)
{
  LOG_INFO << "Loading Level Three" << std::endl;
}

LevelThree::~LevelThree()
{
}

int LevelThree::unitOutOfSpace(ECS::Entity entity)
{
  if (_mapEngine.deleteObject(entity) == 0) {
    _ecs.destroyEntity(entity);
  }
  return 0;
}

void LevelThree::unitDie(ECS::Entity entity)
{
  _mapEngine.deleteObject(entity);
}
