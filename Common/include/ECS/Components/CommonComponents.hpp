/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-13T20:15:43+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-15T22:36:07+01:00
 */


#pragma once

#include "ECS/Component.hpp"
#include "ECS/Entity.hpp"

#include <string>

namespace ECS
{
  namespace Components
  {
    struct Position : ECS::Component
    {
      Position(float _x, float _y)
        : x(_x),
          y(_y)
        {}

      float x;
      float y;

    };

    struct Direction : ECS::Component
    {
      explicit Direction(float _xDirection, float _yDirection, float _speed)
      : xDirection(_xDirection),
      yDirection(_yDirection),
      speed(_speed)
        {}

      float xDirection;
      float yDirection;

      float speed;

    };

    struct Collisionable : ECS::Component
    {
      enum class Type
      {
        NEUTRAL,
        ENNEMY,
        ALLY,
      };
      explicit Collisionable(ECS::Entity _entity, Collisionable::Type _type)
      : entity(_entity),
      type(_type)
        {}

      Entity entity;
      Collisionable::Type type;
    };

    struct Player : ECS::Component
    {
      explicit  Player(const std::string &_name)
        : name(_name)
      {}

      std::string name;
    };
  }
}
