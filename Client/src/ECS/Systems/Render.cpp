/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-20T04:50:36+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-21T04:18:12+01:00
 */


#include  "ECS/Systems/Render.hpp"
#include  "ECS/Components/Components.hpp"
#include  <iostream>

namespace ECS
{
  namespace Systems
  {
  Render::Render(ResourcesManager &resourcesManager, ECS::Manager &ecsManager, sf::RenderWindow &window)
    : System(RENDER_PRIORITY, {ECS::Components::Drawable::Type, ECS::Components::Direction::Type}, ecsManager),
      _window(window),
      _resourcesManager(resourcesManager)
    {}

    void  Render::updateEntity(float delta, Entity e)
    {
      std::shared_ptr<ECS::Components::Drawable> body = getManager().getComponent<ECS::Components::Drawable>(e);
      std::shared_ptr<ECS::Components::Direction> direction = getManager().getComponent<ECS::Components::Direction>(e);
      std::shared_ptr<ECS::Components::Position> position = getManager().getComponent<ECS::Components::Position>(e);

      sf::Sprite &sprite = _resourcesManager.getContent<Sprite>(body->sprite);

      sprite.setPosition(sf::Vector2f(position->x + (direction->xDirection * direction->speed * delta),
        position->y + (direction->yDirection * direction->speed * delta)));
      _window.draw(sprite);

      // std::cout << "RENDER " << direction->direction << std::endl;
    }
  }
}
