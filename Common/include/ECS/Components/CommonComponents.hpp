/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-13T20:15:43+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-21T06:56:23+01:00
 */


#pragma once

#include "ECS/Component.hpp"
#include "ECS/Entity.hpp"

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

    };

    struct Direction : ECS::Component
    {
      explicit Direction(int _xDirection, int _yDirection, int _speed)
      : xDirection(_xDirection),
      yDirection(_yDirection),
      speed(_speed)
        {}

      int xDirection;
      int yDirection;

      int speed;

    };

    struct Collisionable : ECS::Component
    {
      enum class Type
      {
        NEUTRAL,
        ALLY,
        ENEMY
      };

      explicit Collisionable(ECS::Entity _entity, Collisionable::Type _type)
      : entity(_entity),
      type(_type)
        {}

      Entity entity;
      Collisionable::Type type;

    };
  }
}
