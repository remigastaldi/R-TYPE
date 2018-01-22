/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-20T04:50:36+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-22T03:14:38+01:00
 */


#include  "ECS/Systems/Render.hpp"
#include  "ECS/Components/Components.hpp"
#include  <iostream>

namespace ECS
{
  namespace Systems
  {
  Render::Render(ResourcesManager &resourcesManager, ECS::Manager &ecsManager, sf::RenderWindow &window)
    : System(RENDER_PRIORITY, {Alfred::Utils::GetTypeID<ECS::Components::Drawable>()}, ecsManager),
      _window(window),
      _resourcesManager(resourcesManager)
    {}

    void  Render::updateEntity(float delta, Entity e)
    {
      std::shared_ptr<ECS::Components::Drawable> body = getManager().getComponent<ECS::Components::Drawable>(e);
      std::shared_ptr<ECS::Components::Direction> direction = getManager().getComponent<ECS::Components::Direction>(e);
      std::shared_ptr<ECS::Components::Position> position = getManager().getComponent<ECS::Components::Position>(e);

      sf::Sprite &sprite = _resourcesManager.getContent<Sprite>(body->sprite);

      int xDirection = 0;
      int yDirection = 0;
      int speed = 0;

      std::shared_ptr<Store> store = getManager().getStore(Alfred::Utils::GetTypeID<ECS::Components::Drawable>());

      if (direction)
      {
        xDirection = direction->xDirection;
        yDirection = direction->yDirection;
        speed = direction->speed;
      }

      sprite.setPosition(sf::Vector2f(position->x + (xDirection * speed * delta),
        position->y + (yDirection * speed * delta)));
      _window.draw(sprite);
    }
  }
}
