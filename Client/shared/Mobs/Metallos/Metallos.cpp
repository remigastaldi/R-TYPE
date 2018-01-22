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

  _ecs.addComponent<ECS::Components::Position>(_me, pos);
  _ecs.addComponent<ECS::Components::Drawable>(_me, ECS::Components::Drawable(_TEXTURE_NAME));
  _ecs.addComponent<ECS::Components::Collisionable>(_me, ECS::Components::Collisionable(_me));
  _ecs.addComponent<ECS::Components::Stats>(_me, ECS::Components::Stats(1));

  _ecs.updateEntityToSystems(_me);

  _movement = std::make_unique<IMove *>(_loader.move.get(_MOVE_NAME)(_ecs, _event, _loader, _me));
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

  _curTime -= 1;

  if (_curTime <= 0)
  {
    _curTime = _timeBetweenAttack;
    //Spawn an attack
    IAttack *curAttack = _loader.attack.get(_ATTACK_NAME)(_ecs, _event, _loader, _me);
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
  {
    if (it.first == by)
      (*it.second)->playerHit(to);
    if (it.first == to)
      (*it.second)->playerHit(by);
  }
}

void Metallos::unitOutOfSpace(ECS::Entity entity)
{
  _attacks.erase(entity);
}
