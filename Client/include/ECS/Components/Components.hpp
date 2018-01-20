/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-20T18:54:40+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-20T19:03:04+01:00
 */


#pragma once

#include  "ECS/Component.hpp"
#include  <string>

namespace ECS
{
  namespace Components
  {
    struct Drawable : ECS::Component
    {
      explicit Drawable(const std::string &_sprite)
        : sprite(_sprite)
        {}

      std::string sprite;

      static const ECS::ComponentType Type = 100;
    };
  }
}
