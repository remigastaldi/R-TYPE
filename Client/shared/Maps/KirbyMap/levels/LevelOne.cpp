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
    if (_mobs.empty())
      _isEnd = true;
    return;
  }

  if (_timeLeft > -10)
    _timeLeft -= 1;

  if (_timeLeft < 0 && _mobs.empty()) {
    _timeLeft = _timeBetweenMobSpawn;
    _nbMobSpawn -= 1;

    //Spawn a mob
    LOG_INFO << "Spawning a mob " << _nbMobSpawn << std::endl;

    std::shared_ptr<IMob> tmp;
    tmp.reset(_loader.mob.get("Metallos")(_ecs, _event, _loader, ECS::Components::Position(1800, 900)));
    _mobs[tmp->getID()] = tmp;
  }

  //Update mobs
  for (auto &it : _mobs)
    it.second->update();
}

LevelOne::LevelOne(ECS::Manager &ecs, EventManager::Manager &event, LibLoader &libloader) :
  ILevels(ecs, event, libloader),
  _ecs(ecs),
  _event(event),
  _loader(libloader)
{
  LOG_INFO << "Loading Level One" << std::endl;
}

LevelOne::~LevelOne()
{
}

void LevelOne::playerHit(ECS::Entity by, ECS::Entity to)
{
  for (auto &it : _mobs) {
    if (it.first == to) {
//      if ((*it.second)->isYouWhenHit(by))
//      {
      LOG_INFO << "Mob is hit " << to << " " << by << std::endl;

      _ecs.getComponent<ECS::Components::Stats>(to)->health -= 1;
      if (_ecs.getComponent<ECS::Components::Stats>(to)->health <= 0) {
        _mobs.erase(to);
      }
      return;
    }
    if (it.first == by) {
      LOG_INFO << "Mob is hit " << by << " " << to << std::endl;

      _ecs.getComponent<ECS::Components::Stats>(by)->health -= 1;
      if (_ecs.getComponent<ECS::Components::Stats>(by)->health <= 0) {
        _mobs.erase(by);
      }
      return;
    } else {
      //Mob is not hit, check if one of his attack is responsible for this
      it.second->playerHit(by, to);
    }
  }
}

void LevelOne::unitOutOfSpace(ECS::Entity entity)
{
  if (_mobs.count(entity) > 0) {
    LOG_SUCCESS << "Mob out of space deleted" << std::endl;
    _mobs.erase(entity);
    return;
  }

  for (auto &it : _mobs)
    it.second->unitOutOfSpace(entity);
}
