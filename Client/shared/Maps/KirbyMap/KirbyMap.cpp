/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-02-14T19:31:45+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-21T01:09:42+01:00
 */


#include <Maps/KirbyMap/levels/LevelOne.hpp>
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

  
  _listeners["UnitDie"] = _event.listen<int, ECS::Entity>("UnitDie", [&](ECS::Entity e) -> int {
    if (!_isEnd) {
      _levels[_wave]->unitDie(e);
    }
	return 0;
  });

  _listeners["UnitOutOfSpace"] = _event.listen<int, ECS::Entity>("UnitOutOfSpace", [&](ECS::Entity e) -> int {
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

  LOG_INFO << "Adding Level Done" << std::endl;

  _event.fire<int, std::string>("printAlert", _levels[_wave]->getName());

  std::shared_ptr<Ship> ship(std::make_shared<Ship>(_gameManagers, _mapEngine));
  _mapEngine.addObject<Ship>(ship->getID(), ship);
}

KirbyMap::~KirbyMap()
{
  _event.unlisten<int, ECS::Entity>("UnitDie", _listeners["UnitDie"]);
  _event.unlisten<int, ECS::Entity>("UnitOutOfSpace", _listeners["UnitOutOfSpace"]);
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
      //TODO EVENT POUR ECRIRE SUR GUI LE NOM DU NIVEAU
      _levels[_wave]->enter();
      LOG_INFO << _levels[_wave]->getName() << std::endl;
    } else {
      _isEnd = true;
    }
  }
}

bool KirbyMap::isEnd()
{
  //TODO
  return _isEnd;
}
