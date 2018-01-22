/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-21T04:36:33+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-22T05:47:50+01:00
 */


#include  "ECS/Systems/Collision.hpp"

#include  "ECS/Components/CommonComponents.hpp"
#include <iostream>

namespace ECS
{
  namespace Systems
  {
    Collision::Collision(EventManager::Manager &eventManager, ResourcesManager &resourceManager, ECS::Manager &ecsManager)
      : System(COLLISION_PRIORITY, {Alfred::Utils::GetTypeID<ECS::Components::Position>(), Alfred::Utils::GetTypeID<ECS::Components::Collisionable>(),
          Alfred::Utils::GetTypeID<ECS::Components::Drawable>()}, ecsManager),
          _eventManager(eventManager),
          _resourcesManager(resourceManager)
      { }

    void Collision::init(void)
    {
      _eventManager.addEvent<void, ECS::Entity, ECS::Entity>("Collision");
    }

    void Collision::updateEntity(float delta, Entity e)
    {
      (void) delta;
      std::shared_ptr<ECS::Components::Position> position = getManager().getComponent<ECS::Components::Position>(e);
      std::shared_ptr<ECS::Components::Drawable> entityDrawable = getManager().getComponent<ECS::Components::Drawable>(e);

      sf::Sprite &entitySprite = _resourcesManager.getContent<Sprite>(entityDrawable->sprite);

      std::shared_ptr<Store> store = getManager().getStore(Alfred::Utils::GetTypeID<ECS::Components::Collisionable>());
      std::set<ECS::Entity> entity = store->getEntities();

      for (auto &  it : entity)
      {
        if (it == e)
          continue;
        std::shared_ptr<ECS::Components::Drawable> drawable = getManager().getComponent<ECS::Components::Drawable>(it);

        sf::Sprite &sprite = _resourcesManager.getContent<Sprite>(drawable->sprite);

        if (sprite.getGlobalBounds().intersects(entitySprite.getGlobalBounds()))
        {
          _eventManager.fire<void, ECS::Entity, ECS::Entity>("Collision", it, e);
        }
      }
    }
  }
}
