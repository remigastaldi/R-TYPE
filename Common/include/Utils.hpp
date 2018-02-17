/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-02-16T19:16:26+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-16T19:26:33+01:00
 */


#pragma once

#include <cmath>

namespace Utils
{
  inline bool compareFloat(float A, float B, float epsilon = 0.0005f)
  {
    return (std::fabs(A - B) < epsilon);
  }
}
