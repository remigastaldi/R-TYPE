#include <ECS/Components/Stats.hpp>
#include "LevelTwo.hpp"

const std::string &LevelTwo::getName()
{
  return _name;
}

void LevelTwo::enter()
{
  LOG_ERROR << "Je rentre dans le niveau deux" << std::endl;
}

void LevelTwo::exit()
{
  LOG_ERROR << "Bravo tu as fini le niveau deux !" << std::endl;
}

bool LevelTwo::isEnd()
{
  return _isEnd;
}

void LevelTwo::update()
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
    _nbMobSpawn -= 3;


    std::shared_ptr<IMob> tmp(_loader.mob.get("Metallos")(_gameManagers, _mapEngine, ECS::Components::Position(1800, 900)));
    std::shared_ptr<IMob> tmp2(_loader.mob.get("Metallos")(_gameManagers, _mapEngine, ECS::Components::Position(1800, 400)));
    std::shared_ptr<IMob> tmp3(_loader.mob.get("Metallos")(_gameManagers, _mapEngine, ECS::Components::Position(1800, 200)));
    _mapEngine.addObject<IMob>(tmp->getID(), tmp);
    _mapEngine.addObject<IMob>(tmp2->getID(), tmp2);
    _mapEngine.addObject<IMob>(tmp3->getID(), tmp3);
  }

  _mapEngine.updateObjects();
}

LevelTwo::LevelTwo(GameEngine::GameManagers &gameManagers, MapEngine &mapEngine) :
  ILevels(gameManagers, mapEngine),
  _gameManagers(gameManagers),
  _ecs(gameManagers.ecs),
  _event(gameManagers.event),
  _loader(gameManagers.libLoader),
  _mapEngine(mapEngine),
  _mobs()
{
  LOG_INFO << "Loading Level Two" << std::endl;
}

LevelTwo::~LevelTwo()
{
}

int LevelTwo::unitOutOfSpace(ECS::Entity entity)
{
  _mapEngine.deleteObject(entity);
  return 0;
}

void  LevelTwo::unitDie(ECS::Entity entity)
{
  _mapEngine.deleteObject(entity);
}
