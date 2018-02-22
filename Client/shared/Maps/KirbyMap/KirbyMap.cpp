/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-02-14T19:31:45+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-21T09:20:43+01:00
 */


#include <Maps/KirbyMap/levels/LevelOne.hpp>
#include <Maps/KirbyMap/levels/LevelTwo.hpp>
#include <Maps/KirbyMap/levels/LevelThree.hpp>
#include "KirbyMap.hpp"

KirbyMap::KirbyMap(GameEngine::GameManagers &gameManagers) :
  _listeners(),
  _gameManagers(gameManagers),
  _ecs(gameManagers.ecs),
  _event(gameManagers.event),
  _loader(gameManagers.libLoader),
  _levels(),
  _mapEngine(gameManagers)
{
  Logger::get().setOutput(CONSOLE_LOG);

  _mapEngine.addParallax("parallax_01", 0.3, false);
  _mapEngine.addParallax("parallax_02", 0.5, false);
  _mapEngine.addParallax("parallax_03", 1, true);


  _listeners["UnitDieEvent"] = _event.listen<int, ECS::Entity>("UnitDieEvent", [&](ECS::Entity e) -> int {
    if (!_isEnd) {
      _levels[_wave]->unitDie(e);
    }
	return 0;
  });

  _listeners["UnitOutOfSpaceEvent"] = _event.listen<int, ECS::Entity>("UnitOutOfSpaceEvent", [&](ECS::Entity e) -> int {
    if (!_isEnd) {
      _levels[_wave]->unitOutOfSpace(e);
    }
	return 0;
  });


  //Adding levels
  LOG_INFO << "Adding Level: " << std::endl;

  std::shared_ptr<ILevels> tmp;
  tmp.reset(new LevelOne(_gameManagers, _mapEngine));
  _levels.push_back(tmp);
  std::shared_ptr<ILevels> tmp2;
  tmp2.reset(new LevelTwo(_gameManagers, _mapEngine));
  _levels.push_back(tmp2);
  std::shared_ptr<ILevels> tmp3;
  tmp3.reset(new LevelThree(_gameManagers, _mapEngine));
  _levels.push_back(tmp3);


  LOG_WARNING << "Adding Level Done" << std::endl;

  _event.fire<int, std::string>("printAlert", _levels[_wave]->getName());

  std::shared_ptr<Ship> ship(std::make_shared<Ship>(_gameManagers, _mapEngine));
  _mapEngine.addObject<Ship>(ship->getID(), ship);
}

KirbyMap::~KirbyMap()
{
  _event.unlisten<int, ECS::Entity>("UnitDieEvent", _listeners["UnitDieEvent"]);
  _event.unlisten<int, ECS::Entity>("UnitOutOfSpaceEvent", _listeners["UnitOutOfSpaceEvent"]);
  _mapEngine.clearObjects();
}

const std::pair<int, int> &KirbyMap::getNeededLevel() const
{
  return _neededLevel;
}

void KirbyMap::update()
{
  if (_levels.size() <= _wave) {
    _isEnd = true;
    return;
  }

  _levels[_wave]->update();
  if (_levels[_wave]->isEnd()) {
    _levels[_wave]->exit();
    _wave += 1;

    if (_wave < _levels.size()) {
      _event.fire<int, std::string>("printAlert", _levels[_wave]->getName());
      _levels[_wave]->enter();
      LOG_INFO << _levels[_wave]->getName() << std::endl;
    } else {
      _isEnd = true;
    }
  }
}

bool KirbyMap::isEnd()
{
  return _isEnd;
}
