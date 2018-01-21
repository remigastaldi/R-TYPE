#include <ECS/Components/Components.hpp>
#include "BasicAttack.hpp"

BasicAttack::BasicAttack(ECS::Manager &ecs, EventManager::Manager &event) :
  IAttack(ecs, event),
  _ecs(ecs),
  _event(event)
{
  _entity = _ecs.createEntity();

  ECS::Components::Stats tmp;
  tmp.health = 1;

  _ecs.addComponent<ECS::Components::Stats>(_entity, tmp);
}

BasicAttack::~BasicAttack()
{
  for (auto it : _move)
    delete (it);
}

const std::string &BasicAttack::getName() const
{
  return _name;
}

void BasicAttack::update(const float time)
{
  if (_precTime != 0) {
    _timeLeft -= time - _precTime;
    if (_timeLeft <= 0) {
      //spawn bullet
      _timeLeft = _timeBetweenHit;
      attack();
    }
  }
  _precTime = time;
}

ECS::Entity BasicAttack::getID()
{
  return _entity;
}

void BasicAttack::giveOwnerEntity(ECS::Entity entity)
{
  _ownerEntity = entity;
}

void BasicAttack::attack()
{
  ECS::Entity e = _ecs.createEntity();
  _attacks.push_back(e);

  _ecs.addComponent<ECS::Components::Position>(e, *_ecs.getComponent<ECS::Components::Position>(_ownerEntity).get());
  _ecs.addComponent<ECS::Components::Direction>(e, *_ecs.getComponent<ECS::Components::Direction>(_ownerEntity).get());
  _ecs.addComponent<ECS::Components::Drawable>(e, ECS::Components::Drawable("ennemy1"));
}

void BasicAttack::move()
{
  for (auto &it: _move)
    it->update(_precTime);
}

void BasicAttack::playerHit(ECS::Entity entity)
{
  _ecs.getComponent<ECS::Components::Stats>(entity).get()->health -= _baseDamage;
}
