/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-20T18:54:40+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-22T10:09:56+01:00
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
    };

    struct Animated : ECS::Component
    {
      explicit Animated(const std::string &_sprite, int _timeStamp, int _xSize, int _animationNumber)
        : sprite(_sprite),
        counter(_timeStamp),
        timestamp(_timeStamp),
        xSize(_xSize),
        currentAnimationNumber(0),
        animationNumber(_animationNumber)
        {}

      std::string sprite;
      int   counter;
      int   timestamp;
      int   xSize;
      int   currentAnimationNumber;
      int   animationNumber;
    };
  }
}
