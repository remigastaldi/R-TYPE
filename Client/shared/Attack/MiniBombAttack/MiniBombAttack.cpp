#include "MiniBombAttack.hpp"

MiniBombAttack::MiniBombAttack(GameEngine::GameManagers &gameManagers, MapEngine &mapEngine, ECS::Entity owner) :
  IAttack(gameManagers, mapEngine, owner),
  _beforeExplosion(100),
  _gameManagers(gameManagers),
  _ecs(gameManagers.ecs),
  _event(gameManagers.event),
  _loader(gameManagers.libLoader),
  _mapEngine(mapEngine),
  _ownerEntity(owner),
  _entity(gameManagers.ecs.createEntity()),
  _attacks(),
  _move(),
  _spriteName(),
  toDel()
{
  Logger::get().setOutput(CONSOLE_LOG);

  std::shared_ptr<Texture> texture = _gameManagers.resources.get<Texture>(_TEXTURE);
  _spriteName = "mini_bomb_attack_sprite[" + std::to_string(_entity) + "]";

  Sprite sprite(_spriteName, *texture);
  _gameManagers.resources.addResource<Sprite>(_spriteName, sprite);

  sf::Sprite &spriteMissiles = _gameManagers.resources.getContent<Sprite>(_spriteName);
  spriteMissiles.setRotation(-90);

  _ecs.addComponent<ECS::Components::Collisionable>(_entity, ECS::Components::Collisionable(_entity,
                                                                                            ECS::Components::Collisionable::Type::ENEMY_MISSILE));
  _ecs.addComponent<ECS::Components::Drawable>(_entity, ECS::Components::Drawable(_spriteName));
  ECS::Components::Position pos = *_ecs.getComponent<ECS::Components::Position>(_ownerEntity);
  pos.x -= 150;
  _ecs.addComponent<ECS::Components::Position>(_entity, pos);
  _ecs.addComponent<ECS::Components::Damages>(_entity, ECS::Components::Damages(1));
  _ecs.updateEntityToSystems(_entity);

  std::shared_ptr<IMove> aM(_loader.move.get(_gameManagers.config.getKey("private dsl ugly for bomb"))(_gameManagers, _entity, -1, 5));
  _mapEngine.addObject(aM->getID(), aM);
}

MiniBombAttack::~MiniBombAttack()
{
  _gameManagers.resources.release(_spriteName);
  _ecs.destroyEntity(_entity);
}

void MiniBombAttack::update()
{}

ECS::Entity MiniBombAttack::getID() const
{
  return _entity;
}

void MiniBombAttack::move()
{
  _move->update();
}
