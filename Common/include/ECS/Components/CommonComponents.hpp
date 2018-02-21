/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-13T20:15:43+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-20T22:14:43+01:00
 */


#pragma once

#include "ECS/Component.hpp"
#include "ECS/Entity.hpp"

#include <string>

namespace ECS
{
  namespace Components
  {
    struct Position : public ECS::Component
    {
      Position(float _x, float _y)
        : x(_x),
          y(_y)
        {}

      float x;
      float y;

    };

    struct Direction : public ECS::Component
    {
      Direction(float _xDirection, float _yDirection, float _speed)
        : xDirection(_xDirection),
        yDirection(_yDirection),
        speed(_speed)
      {}

      float xDirection;
      float yDirection;

      float speed;

    };

    struct Collisionable : public ECS::Component
    {
      enum class Type
      {
        NEUTRAL,
        ENEMY,
        ALLY,
        ALLY_MISSILE,
        ENEMY_MISSILE
      };
      Collisionable(ECS::Entity _entity, Collisionable::Type _type)
        : entity(_entity),
        type(_type)
      {}

      Entity entity;
      Collisionable::Type type;
    };

    struct CollisionFrame : public ECS::Component
    {
      CollisionFrame(ECS::Entity _entity, int _nbFrames)
        : entity(_entity),
        nbFrames(_nbFrames)
      {}

      Entity  entity;
      int     nbFrames;
    };

    struct Player : public ECS::Component
    {
      explicit  Player(const std::string &_name)
        : name(_name)
      {}

      std::string name;
    };

    struct Health : public ECS::Component
    {
      explicit Health(int _health)
        : health(_health)
      {}

      int health;
    };

    struct Damages : public ECS::Component
    {
      explicit Damages(int _damages)
        : damages(_damages)
      {}

      int damages;
    };

    struct Ennemy : public ECS::Component
    {
      explicit Ennemy() {};
    };
  }
}
