/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-22T07:43:06+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-22T10:17:37+01:00
 */


#include  "ECS/Systems/Animation.hpp"

namespace ECS
{
  namespace Systems
  {
  Animation::Animation(EventManager::Manager &eventManager, ResourcesManager &resourceManager, ECS::Manager &ecsManager)
    : System(ANIMATION_PRIORITY, {ecsManager.GetTypeID<ECS::Components::Drawable>(), ecsManager.GetTypeID<ECS::Components::Animated>()}, ecsManager),
      _resourcesManager(resourceManager),
      _eventManager(eventManager)
      {}

    void Animation::updateEntity(float delta, Entity e)
    {
      (void)delta;
      std::shared_ptr<ECS::Components::Animated> animated = getManager().getComponent<ECS::Components::Animated>(e);
      std::shared_ptr<ECS::Components::Drawable> drawable = getManager().getComponent<ECS::Components::Drawable>(e);

      sf::Sprite &sprite = _resourcesManager.getContent<Sprite>(drawable->sprite);
      if (animated->counter == animated->timestamp)
      {
        sprite.setTextureRect(sf::IntRect(animated->xSize * animated->currentAnimationNumber, 0, animated->xSize, sprite.getGlobalBounds().height));
        if (animated->currentAnimationNumber == animated->animationNumber)
          getManager().destroyEntity(e);
        else
          animated->currentAnimationNumber++;
        animated->counter = 0;
      }
      else
        animated->counter++;
    }
  }
}
