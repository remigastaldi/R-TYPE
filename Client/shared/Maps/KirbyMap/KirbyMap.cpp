/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-02-14T19:31:45+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-16T17:18:02+01:00
 */


#include <Maps/KirbyMap/levels/LevelOne.hpp>
#include "KirbyMap.hpp"

KirbyMap::KirbyMap(GameEngine::GameManagers &gameManagers) :
  _listener(),
  _listenerOutOfSpace(),
  _gameManagers(gameManagers),
  _ecs(gameManagers.ecs),
  _event(gameManagers.event),
  _loader(gameManagers.libLoader),
  _levels(),
  _mapEngine(gameManagers)
{
  Logger::get().setOutput(CONSOLE_LOG);

  _mapEngine.addParallax("../../Client/media/img/Parallax/background_01_parallax_01.png", 0.3, false);
  _mapEngine.addParallax("../../Client/media/img/Parallax/background_01_parallax_02.png", 0.5, false);
  _mapEngine.addParallax("../../Client/media/img/Parallax/background_01_parallax_03.png", 1, true);

  _listener = _event.listen<void, ECS::Entity, ECS::Entity>("Collision", [&](ECS::Entity by,
                                                                             ECS::Entity to) -> void {

    if (!_isEnd) {
      _levels[_wave]->playerHit(by, to);
    }
  });

  _listenerOutOfSpace = _event.listen<void, ECS::Entity>("UnitOutOfSpace", [&](ECS::Entity e) -> void {
    if (!_isEnd) {
      _levels[_wave]->unitOutOfSpace(e);
    }
  });


  //Adding levels
  LOG_INFO << "Adding Level: " << std::endl;

  std::shared_ptr<ILevels> tmp;
  tmp.reset(new LevelOne(_gameManagers, _mapEngine));
  _levels.push_back(tmp);

  LOG_INFO << "Adding Level Done" << std::endl;

  _event.fire<void, const std::string &>("printAlert", _levels[_wave]->getName());

  std::shared_ptr<Ship> ship(std::make_shared<Ship>(_gameManagers, _mapEngine));
  _mapEngine.addObject<Ship>(ship->getID(), ship);
}

KirbyMap::~KirbyMap()
{
  _event.unlisten<void, ECS::Entity, ECS::Entity>("Collision", _listener);
  _event.unlisten<void, ECS::Entity>("UnitOutOfSpace", _listenerOutOfSpace);
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
      _event.fire<void, const std::string &>("printAlert", _levels[_wave]->getName());
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
