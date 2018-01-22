#include "Metallos.hpp"

Metallos::Metallos(ECS::Manager &ecs, EventManager::Manager &event, LibLoader &libLoader, ECS::Components::Position pos) :
  IMob(ecs, event, libLoader, pos),
  _ecs(ecs),
  _event(event),
  _loader(libLoader)
{
  Logger::get().setOutput(CONSOLE_LOG);

  LOG_INFO << "Creating Metaloss" << std::endl;

  _me = _ecs.createEntity();

  ECS::Components::Stats tmp;
  tmp.health = 1;

  _ecs.addComponent<ECS::Components::Stats>(_me, tmp);
  _ecs.addComponent<ECS::Components::Position>(_me, pos);
  _ecs.addComponent<ECS::Components::Drawable>(_me, ECS::Components::Drawable("playersSpaceship"));

  _movement = std::make_unique<IMove *>(_loader.move.get("UpAndDownMove")(_ecs, _event, _loader, _me));
}

Metallos::~Metallos()
{
  _ecs.destroyEntity(_me);
}

const int Metallos::getDifficulty()
{
  return _difficulty;
}

void Metallos::update()
{
  //Update movement
  (*_movement)->update();

  //Update attacks
  for (auto &it : _attacks)
    (*it.second)->update();

  _curTime += 1;
  if (_curTime >= _timeBetweenAttack)
  {
    //Spawn an attack ?
    _curTime = 0;
    IAttack *curAttack = _loader.attack.get("BasicAttack")(_ecs, _event, _loader, _me);
    _attacks[curAttack->getID()] = std::make_unique<IAttack *>(curAttack);
  }
}

ECS::Entity Metallos::getID()
{
  return _me;
}

void Metallos::playerHit(ECS::Entity by, ECS::Entity to)
{
  for (auto &it: _attacks)
    if (it.first == by)
      (*it.second)->playerHit(to);
}
