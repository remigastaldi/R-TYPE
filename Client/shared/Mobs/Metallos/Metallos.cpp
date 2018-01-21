#include "Metallos.hpp"

Metallos::Metallos(ECS::Manager &ecs, EventManager::Manager &event) :
  IMob(ecs, event),
  _ecs(ecs),
  _event(event)
{
  _me = _ecs.createEntity();
//  _ecs.addComponent<ECS::Components::(_me)
}

Metallos::~Metallos()
{
}

const int Metallos::getDifficulty()
{
  return _difficulty;
}

const std::string &Metallos::getName() const
{
  return _name;
}

void Metallos::update(const float time)
{

}

ECS::Entity Metallos::getID()
{
  return _me;
}

void Metallos::playerHit(ECS::Entity entity)
{
  _attack->playerHit(entity);
}
