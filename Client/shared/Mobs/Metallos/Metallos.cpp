/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-22T10:02:46+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-22T10:24:41+01:00
 */


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

  LOG_INFO << "Entity ID " << _me << std::endl;

  _ecs.addComponent<ECS::Components::Position>(_me, pos);
  _ecs.addComponent<ECS::Components::Drawable>(_me, ECS::Components::Drawable(_TEXTURE_NAME));
  _ecs.addComponent<ECS::Components::Collisionable>(_me, ECS::Components::Collisionable(_me, ECS::Components::Collisionable::Type::ENNEMY));
  _ecs.addComponent<ECS::Components::Stats>(_me, ECS::Components::Stats(1));

  _ecs.updateEntityToSystems(_me);

  std::shared_ptr<IMove> tmp;
  tmp.reset(_loader.move.get(_MOVE_NAME)(_ecs, _event, _loader, _me));
  _movement = tmp;
}

Metallos::~Metallos()
{
  LOG_SUCCESS << "Metaloss se detruit" << std::endl;
//  _ecs.destroyEntity(_me);
}

const int Metallos::getDifficulty()
{
  return _difficulty;
}

void Metallos::update()
{
  //Update movement
  _movement->update();

  //Update attacks
  for (auto &it : _attacks)
    it.second->update();

  _curTime -= 1;

  if (_curTime <= 0)
  {
    _curTime = _timeBetweenAttack;
    //Spawn an attack
    std::shared_ptr<IAttack> tmp;
    tmp.reset(_loader.attack.get(_ATTACK_NAME)(_ecs, _event, _loader, _me));
    _attacks[tmp->getID()] = tmp;
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
      it.second->playerHit(to);
    if (it.first == to)
      it.second->playerHit(by);
  }
}

void Metallos::unitOutOfSpace(ECS::Entity entity)
{
  _attacks.erase(entity);
}
