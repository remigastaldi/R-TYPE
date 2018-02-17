/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-02-15T01:38:28+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-17T12:56:14+01:00
 */


#include  "MapEngine.hpp"

MapEngine::MapEngine(GameEngine::GameManagers &gameManagers)
  : _gameManagers(gameManagers),
  _objects(),
  _parallaxItems()
  {}


void  MapEngine::addParallax(const std::string &layer, float speedLayer, bool flipVerticaly)
{
  ECS::Entity entity = _gameManagers.ecs.createEntity();
  ECS::Entity flippedEntity = _gameManagers.ecs.createEntity();

  std::shared_ptr<Texture> texture(_gameManagers.resources.load<Texture>("layerTexture[" + std::to_string(_parallaxItems.size() + 1) + "]", layer));

  std::string spriteName = "layerSprite[" + std::to_string(_parallaxItems.size() + 1) + "]";
  std::string flippedSpriteName = "layerFlippedSprite[" + std::to_string(_parallaxItems.size() + 1) + "]";
  Sprite sprite(spriteName, *texture);
  Sprite flippedSprite(flippedSpriteName, *texture);

  sf::FloatRect globalBounds = sprite.getContent().getGlobalBounds();

  if (flipVerticaly)
    flippedSprite.getContent().setTextureRect(sf::IntRect(globalBounds.width, globalBounds.height, -globalBounds.width, -globalBounds.height));
  else
    flippedSprite.getContent().setTextureRect(sf::IntRect(globalBounds.width, 0, -globalBounds.width, globalBounds.height));

  _gameManagers.resources.addResource<Sprite>(spriteName, sprite);
  _gameManagers.resources.addResource<Sprite>(flippedSpriteName, flippedSprite);

  _gameManagers.ecs.addComponent<ECS::Components::Position>(entity, ECS::Components::Position(0.f, 0.f));
  _gameManagers.ecs.addComponent<ECS::Components::Position>(flippedEntity, ECS::Components::Position(sprite.getContent().getGlobalBounds().width, 0.f));

  _gameManagers.ecs.addComponent<ECS::Components::Drawable>(entity, ECS::Components::Drawable(spriteName));
  _gameManagers.ecs.addComponent<ECS::Components::Drawable>(flippedEntity, ECS::Components::Drawable(flippedSpriteName));

  _gameManagers.ecs.addComponent<ECS::Components::Parallax>(entity, ECS::Components::Parallax(-1, 0, speedLayer));
  _gameManagers.ecs.addComponent<ECS::Components::Parallax>(flippedEntity, ECS::Components::Parallax(-1, 0, speedLayer));

  _gameManagers.ecs.updateEntityToSystems(entity);
  _gameManagers.ecs.updateEntityToSystems(flippedEntity);

  _parallaxItems.emplace_back(entity);
  _parallaxItems.emplace_back(flippedEntity);
}

void  MapEngine::clearParallax(void)
{
  for (const auto & it : _parallaxItems)
  {
    //_gameManagers.resources.release(_parallaxItems.getTextureName());
    _gameManagers.ecs.destroyEntity(it);
  }
}
