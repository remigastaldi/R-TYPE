/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-20T04:48:40+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-22T09:38:15+01:00
 */


#pragma once

#include  "Resources.hpp"
#include  "ECS/Manager.hpp"

#include  "ECS/Systems/SystemsPriotity.hpp"
#include  "ECS/Components/Components.hpp"

#include  <SFML/Graphics.hpp>

namespace ECS
{
  namespace Systems
  {
    class Render : public System
    {
    public:
      Render(ResourcesManager &resourcesManager, ECS::Manager &ecsManager, sf::RenderWindow &window);

      // void update(float delta);
      void updateEntity(float delta, Entity e);

    private:
      sf::RenderWindow  &_window;
      ResourcesManager  &_resourcesManager;
    };
  }
}
