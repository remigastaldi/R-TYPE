/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-02-20T15:48:14+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-21T05:33:24+01:00
 */


#include  "ECS/Systems/SpriteCollisionHandler.hpp"

namespace ECS
{
  namespace Systems
  {
    SpriteCollisionHandler::SpriteCollisionHandler(EventManager::Manager &eventManager, ECS::Manager &ecsManager)
      : System(SPRITE_COLLISION_HANDLER_PRIORITY, { ecsManager.GetTypeID<ECS::Components::CollisionFrame>() }, ecsManager),
      _eventManager(eventManager)
    {
      _eventManager.addEvent<int, std::string>("UnitDieEvent");
    }

    void  SpriteCollisionHandler::updateEntity(float delta, Entity e)
    {
      (void) delta;

      std::shared_ptr<ECS::Components::CollisionFrame>  collisionFrame(getManager().getComponent<ECS::Components::CollisionFrame>(e));

      std::shared_ptr<ECS::Components::Collisionable>  collisionableA(getManager().getComponent<ECS::Components::Collisionable>(e));
      if (collisionableA.get() == nullptr)
        return;
      std::shared_ptr<ECS::Components::Collisionable>  collisionableB(getManager().getComponent<ECS::Components::Collisionable>(collisionFrame->entity));
      if (collisionableB.get() == nullptr)
        return;

      //std::cout << collisionFrame.get() << " " << collisionableA.get() << " " << collisionableB.get() << std::endl;
      if ((collisionableA->type == collisionableB->type)
        || (collisionableA->type == ECS::Components::Collisionable::Type::ENEMY_MISSILE && collisionableB->type == ECS::Components::Collisionable::Type::ENEMY)
        || (collisionableA->type == ECS::Components::Collisionable::Type::ALLY_MISSILE && collisionableB->type == ECS::Components::Collisionable::Type::ALLY))
        return;
      std::shared_ptr<ECS::Components::Health>  healthA(getManager().getComponent<ECS::Components::Health>(e));
      std::shared_ptr<ECS::Components::Health>  healthB(getManager().getComponent<ECS::Components::Health>(collisionFrame->entity));

      std::shared_ptr<ECS::Components::Damages>  damagesA(getManager().getComponent<ECS::Components::Damages>(e));
      std::shared_ptr<ECS::Components::Damages>  damagesB(getManager().getComponent<ECS::Components::Damages>(collisionFrame->entity));

//        std::cout << "Entity " << e <<  " " << collisionFrame->entity << std::endl;
      if (healthA.get() != nullptr && damagesB.get() != nullptr)
      {
      //  std::cout << "1" << " " << healthA->health << " " << damagesB->damages << std::endl;
        healthA->health -= damagesB->damages;
        if ((collisionableB->type == ECS::Components::Collisionable::Type::ENEMY_MISSILE)
          || (collisionableB->type == ECS::Components::Collisionable::Type::ALLY_MISSILE))
        {
          getManager().destroyEntity(collisionFrame->entity);
          _eventManager.fire<int, ECS::Entity>("UnitDieEvent", collisionFrame->entity);
        }
      }
      if (healthB.get() != nullptr && damagesA.get() != nullptr)
      {
        //std::cout << "2" << " " << healthB->health << " " << damagesA->damages << std::endl;
        healthB->health -= damagesA->damages;
        if ((collisionableA->type == ECS::Components::Collisionable::Type::ENEMY_MISSILE)
          || (collisionableA->type == ECS::Components::Collisionable::Type::ALLY_MISSILE))
        {
          getManager().destroyEntity(e);
          _eventManager.fire<int, ECS::Entity>("UnitDieEvent", e);
        }
      }
    }
  }
}
