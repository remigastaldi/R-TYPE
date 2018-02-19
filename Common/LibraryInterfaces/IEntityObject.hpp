/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-02-18T13:01:52+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-18T13:49:56+01:00
 */


#pragma once

#include  "ECS/Entity.hpp"

class IEntityObject
{
public:
  IEntityObject() {};

  virtual ~IEntityObject() = default;

  //virtual void unitOutOfSpace(ECS::Entity) = 0;
  virtual void  update(void) = 0;
  virtual ECS::Entity getID() const = 0;
};
