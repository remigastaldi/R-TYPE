/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-13T19:13:27+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-20T17:38:59+01:00
 */


#pragma once

namespace ECS
{
  #define MOUVEMENT_PRIORITY 1
  #define COLLISION_PRIORITY 2
  #define SPRITE_COLLISION_HANDLER_PRIORITY 3
  #define PARALLAX_PRIORITY 4
  #define HEALTH_PRIORITY 5
  #define ANIMATION_PRIORITY 6
  #define CLEANUP_FRAME_COLLISION_COMPONENTS_PRIORITY 7
  #define RENDER_PRIORITY 100
}
