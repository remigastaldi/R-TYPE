#include "AMobs.hpp"

AMobs::AMobs(GameEngine::GameManagers &gameManagers, MapEngine &mapEngine, ECS::Components::Position pos,
             std::string attack_name, std::string movement_name, std::string texture_name) :
  IMob(gameManagers, mapEngine, pos),
  _ATTACK_NAME(attack_name),
  _MOVE_NAME(movement_name),
  _TEXTURE_NAME(texture_name),
  _me(gameManagers.ecs.createEntity()),
  _gameManagers(gameManagers),
  _ecs(gameManagers.ecs),
  _event(gameManagers.event),
  _loader(gameManagers.libLoader),
  _mapEngine(mapEngine),
  _spriteName()
{
  Logger::get().setOutput(CONSOLE_LOG);

  std::shared_ptr<Texture> texture = _gameManagers.resources.get<Texture>(_TEXTURE_NAME);
  _spriteName = "my_custom_mob_sprite[" + std::to_string(_me) + "]";
  Sprite sprite(_spriteName, *texture);

  sprite.getContent().setRotation(-90);
  sprite.getContent().setScale(0.8, 0.8);
  _gameManagers.resources.addResource<Sprite>(_spriteName, sprite);

  _ecs.addComponent<ECS::Components::Position>(_me, pos);
  _ecs.addComponent<ECS::Components::Drawable>(_me, ECS::Components::Drawable(_spriteName));
  _ecs.addComponent<ECS::Components::Collisionable>(_me, ECS::Components::Collisionable(_me,
                                                                                        ECS::Components::Collisionable::Type::ENEMY_MISSILE));
  _ecs.addComponent<ECS::Components::Health>(_me, ECS::Components::Health(2));

  _ecs.updateEntityToSystems(_me);

  std::shared_ptr<IMove> tmp(_loader.move.get(_MOVE_NAME)(_gameManagers, _me, 0, 2));
  _mapEngine.addObject<IMove>(tmp->getID(), tmp);
}

AMobs::~AMobs()
{
  _gameManagers.resources.release(_spriteName);
  _ecs.destroyEntity(_me);
}

int AMobs::getDifficulty() const
{
  return _difficulty;
}

void AMobs::update()
{
  _curTime -= 1;

  if (_curTime <= 0) {
    _curTime = _timeBetweenAttack;

    std::shared_ptr<IAttack> tmp(_loader.attack.get(_ATTACK_NAME)(_gameManagers, _mapEngine, _me));
    _mapEngine.addObject<IAttack>(tmp->getID(), tmp);
  }
}

ECS::Entity AMobs::getID() const
{
  return _me;
}

void AMobs::unitOutOfSpace(ECS::Entity entity)
{
  (void)entity;
//  _attacks.erase(entity);
}