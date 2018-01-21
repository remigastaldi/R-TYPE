/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-13T20:15:43+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-21T02:59:38+01:00
 */


#pragma once

#include "ECS/Component.hpp"

namespace ECS
{
  namespace Components
  {
    struct Position : ECS::Component
    {
      Position(size_t _x, size_t _y)
        : x(_x),
          y(_y)
        {}

      size_t x;
      size_t y;

      static const ECS::ComponentType Type = 1;
    };

    struct Direction : ECS::Component
    {
      explicit Direction(int _direction)
      : direction(_direction)
        {}

      int direction;

      static const ECS::ComponentType Type = 100;
    };
  }
}
