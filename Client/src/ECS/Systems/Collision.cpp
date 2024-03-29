/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-21T04:36:33+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-21T05:34:15+01:00
 */


#include  "ECS/Systems/Collision.hpp"

#include  "ECS/Components/CommonComponents.hpp"

namespace ECS
{
  namespace Systems
  {
    Collision::Collision(EventManager::Manager &eventManager, ResourcesManager &resourceManager, ECS::Manager &ecsManager)
      : System(COLLISION_PRIORITY, {ecsManager.GetTypeID<ECS::Components::Position>(), ecsManager.GetTypeID<ECS::Components::Collisionable>(),
          ecsManager.GetTypeID<ECS::Components::Drawable>()}, ecsManager),
          _resourcesManager(resourceManager),
          _eventManager(eventManager)
      { }

    void Collision::init(void)
    {    }

    void Collision::updateEntity(float delta, Entity e)
    {
      (void) delta;
      std::shared_ptr<ECS::Components::Position> position = getManager().getComponent<ECS::Components::Position>(e);
      std::shared_ptr<ECS::Components::Drawable> entityDrawable = getManager().getComponent<ECS::Components::Drawable>(e);

      sf::Sprite &entitySprite = _resourcesManager.getContent<Sprite>(entityDrawable->sprite);

      std::shared_ptr<Store> store = getManager().getStore(getManager().GetTypeID<ECS::Components::Collisionable>());
      std::set<ECS::Entity> entities = store->getEntities();

      for (auto &  it : entities)
      {
        if (it == e)
          continue;

        std::shared_ptr<ECS::Components::Drawable> drawable = getManager().getComponent<ECS::Components::Drawable>(it);

        sf::Sprite &sprite = _resourcesManager.getContent<Sprite>(drawable->sprite);

        if (sprite.getGlobalBounds().intersects(entitySprite.getGlobalBounds()))
        {
          getManager().addComponent<ECS::Components::CollisionFrame>(e, ECS::Components::CollisionFrame(it, 1));
          getManager().updateEntityToSystems(e);
        }
      }
    }
  }
}
