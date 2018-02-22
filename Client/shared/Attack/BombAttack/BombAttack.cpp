#include "BombAttack.hpp"

BombAttack::BombAttack(GameEngine::GameManagers &gameManagers, MapEngine &mapEngine, ECS::Entity owner) :
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
  _EXPLOSION_NAME("bomb_explosion"),
  _spriteName(),
  _bombAnimationName()
{
  Logger::get().setOutput(CONSOLE_LOG);

  std::shared_ptr<Texture> texture = _gameManagers.resources.get<Texture>(_TEXTURE);
  _spriteName = "bomb_attack_sprite[" + std::to_string(_entity) + "]";

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
  // _ecs.addComponent<ECS::Components::Stats>(_entity, ECS::Components::Stats(1));
  _ecs.addComponent<ECS::Components::Damages>(_entity, ECS::Components::Damages(1));

  _ecs.updateEntityToSystems(_entity);

  std::shared_ptr<IMove> tmp(_loader.move.get(_MOVE)(_gameManagers, _entity, -1, 5));
  _mapEngine.addObject(tmp->getID(), tmp);
}

BombAttack::~BombAttack()
{
  _gameManagers.resources.release(_spriteName);
  _gameManagers.resources.release(_bombAnimationName);
  _ecs.destroyEntity(_entity);
}

void BombAttack::update()
{
  if (_beforeExplosion == -42)
    return;

  _beforeExplosion -= 1;

  if (_beforeExplosion <= 0) {
    _beforeExplosion = -42;
    std::shared_ptr<Texture> texture = _gameManagers.resources.get<Texture>(_EXPLOSION_NAME);
    _bombAnimationName = "bomb_attack_explosion_sprite[" + std::to_string(_entity) + "]";

    Sprite sprite(_bombAnimationName, *texture);
    _gameManagers.resources.addResource<Sprite>(_bombAnimationName, sprite);

    auto d = _ecs.getComponent<ECS::Components::Drawable>(_entity);
    d->sprite = _bombAnimationName;

    _ecs.getComponent<ECS::Components::Direction>(_entity)->speed = 0;
    _ecs.getComponent<ECS::Components::Position>(_entity)->x -= 120;

    _ecs.addComponent<ECS::Components::Animated>(_entity, ECS::Components::Animated(_bombAnimationName, 20, 140, 9));

    _ecs.updateEntityToSystems(_entity);

    generateChilds("StraightMove");
    generateChilds("SinusoideMove");
    generateChilds("InverseSinusoideMove");
  }
}

ECS::Entity BombAttack::getID() const
{
  return _entity;
}

void BombAttack::move()
{
  _move->update();
}

void BombAttack::generateChilds(std::string moveName)
{
  _gameManagers.config.setKey("private dsl ugly for bomb", std::move(moveName));
  std::shared_ptr<IAttack> a(_gameManagers.libLoader.attack.get("MiniBombAttack")(_gameManagers, _mapEngine, _entity));
  _mapEngine.addObject<IAttack>(a->getID(), a);
}
