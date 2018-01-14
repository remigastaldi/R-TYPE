/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-13T02:09:37+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-13T20:30:18+01:00
 */


#pragma once

#include <cstddef>

#define INVALID_COMPONENT 0

namespace ECS
{
  typedef size_t ComponentType;

  struct Component
  {
    static const ComponentType Type = INVALID_COMPONENT;
  };

}
