#include "KirbyMap.hpp"

KirbyMap::KirbyMap(ECS::Manager &ecs, EventManager::Manager &event) :
  IMap(ecs, event),
  _ecs(ecs),
  _event(event)
{
  _event.listen<void, int, int, ECS::Entity>("player hit", [&](int x, int y, ECS::Entity player) -> void {
    for (auto &it : _mobs)
      if (it.first == player)
        it.second->playerHit(player);
    LOG_INFO << "Player has been hit !" << std::endl;
  });
}

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
