/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-13T20:15:43+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-22T05:51:46+01:00
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
      Position(size_t _x, size_t _y)
        : x(_x),
          y(_y)
        {}

      int x;
      int y;

    };

    struct Direction : ECS::Component
    {
      explicit Direction(double _xDirection, double _yDirection, int _speed)
      : xDirection(_xDirection),
      yDirection(_yDirection),
      speed(_speed)
        {}

      double xDirection;
      double yDirection;

      int speed;

    };

    struct Collisionable : ECS::Component
    {
      explicit Collisionable(ECS::Entity _entity)
      : entity(_entity)
        {}

      Entity entity;
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
