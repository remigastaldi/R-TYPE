#include "BasicAttack.hpp"

BasicAttack::BasicAttack(ECS::Manager &ecs, EventManager::Manager &event) :
  IAttack(ecs, event),
  _ecs(ecs),
  _event(event)
{
  _entity = _ecs.createEntity();
  _ecs.addComponent<ECS::Components::Stats>(_entity, {.health = 1, .Type = 1});
}

BasicAttack::~BasicAttack()
{
}

const std::string &BasicAttack::getName() const
{
  return _name;
}

void BasicAttack::update(const float time)
{
  if (!_eventSet)
    event.listen<void, int, int, ECS::Entity>("player hit", [&](int x, int y, ECS::Entity playerHit) -> void {
      ecs.getComponent<ECS::Components::Stats>(playerHit).get()->health -= _baseDamage;
    });
}
