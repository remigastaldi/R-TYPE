#include "KirbyMap.hpp"

KirbyMap::~KirbyMap()
{
}

const std::string &KirbyMap::getName() const
{
  return _name;
}

const std::pair<int, int> &KirbyMap::getNeededLevel() const
{
  return _neededLevel;
}

void KirbyMap::update(const float time)
{
}

KirbyMap::KirbyMap(ECS::Manager &ecs, EventManager::Manager &event) :
  IMap(ecs, event)
{
}
