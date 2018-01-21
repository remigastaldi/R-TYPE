#include <Maps/KirbyMap/levels/LevelOne.hpp>
#include "KirbyMap.hpp"

KirbyMap::KirbyMap(ECS::Manager &ecs, EventManager::Manager &event, LibLoader &loader) :
  IMap(ecs, event, loader),
  _ecs(ecs),
  _event(event),
  _loader(loader)
{
  _listener = _event.listen<void, int, int, ECS::Entity, ECS::Entity>("player hit", [&](int x, int y, ECS::Entity by,
                                                                                        ECS::Entity to) -> void {

    (*_levels[_wave])->playerHit(by, to);
  });


  //Adding levels
  _levels.push_back(std::make_unique<ILevels *>(new LevelOne(_ecs, _event, loader)));
}

KirbyMap::~KirbyMap()
{
  _event.unlisten<void, int, int, ECS::Entity, ECS::Entity>("player hit", _listener);
}

const std::pair<int, int> &KirbyMap::getNeededLevel() const
{
  return _neededLevel;
}

void KirbyMap::update()
{
  if (_levels.size() < _wave) {
    _isEnd = true;
    return;
  }

  (*_levels[_wave])->update();
  if ((*_levels[_wave])->isEnd()) {
    (*_levels[_wave])->exit();
    _wave += 1;
    if (_levels.size() < _wave)
      //TODO EVENT POUR ECRIRE SUR GUI LE NOM DU NIVEAU
      (*_levels[_wave])->enter();
    LOG_INFO << (*_levels[_wave])->getName() << std::endl;
  } else
    _isEnd = true;
}

bool KirbyMap::isEnd()
{
  //TODO
  return _isEnd;
}