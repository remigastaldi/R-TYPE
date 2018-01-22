#include <Maps/KirbyMap/levels/LevelOne.hpp>
#include "KirbyMap.hpp"

KirbyMap::KirbyMap(ECS::Manager &ecs, EventManager::Manager &event, LibLoader &loader) :
  IMap(ecs, event, loader),
  _ecs(ecs),
  _event(event),
  _loader(loader)
{
  Logger::get().setOutput(CONSOLE_LOG);

  _listener = _event.listen<void, ECS::Entity, ECS::Entity>("Collision", [&](ECS::Entity by,
                                                                                        ECS::Entity to) -> void {

    (*_levels[_wave])->playerHit(by, to);
  });


  //Adding levels
  LOG_INFO << "Adding Level: " << std::endl;
  _levels.push_back(std::make_unique<ILevels *>(new LevelOne(_ecs, _event, loader)));
  LOG_INFO << "Adding Level Done" << std::endl;
}

KirbyMap::~KirbyMap()
{
  _event.unlisten<void, ECS::Entity, ECS::Entity>("Collision", _listener);
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