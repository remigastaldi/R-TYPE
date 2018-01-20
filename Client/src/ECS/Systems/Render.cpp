/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-20T04:50:36+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-20T19:11:15+01:00
 */


#include  "ECS/Systems/Render.hpp"

#include  <iostream>

namespace ECS
{
  namespace Systems
  {
  Render::Render(ECS::Manager &manager)
    : System(RENDER_PRIORITY, { }, manager)
    {}

    void  Render::updateEntity(float delta, Entity e)
    {
      std::cout << "RENDER" << std::endl;
      // std::shared_ptr<ECS::Drawable> body = getManager().getComponent<ECS::Drawable>(e);
    }
  }
}
