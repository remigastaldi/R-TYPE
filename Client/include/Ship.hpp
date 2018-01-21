/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-20T20:45:49+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-21T02:45:12+01:00
 */


#pragma once

#include  "EventManager.hpp"
#include  "ECS/Manager.hpp"
#include  "Resources.hpp"
#include  "ECS/Components/Components.hpp"

#include  <SFML/System.hpp>
#include  <SFML/Graphics.hpp>

class Ship
{
public:
  Ship(ResourcesManager &resourceManager, EventManager::Manager &eventManager, ECS::Manager &ecsManager);


  void  go_Up(const std::string &data);
  void  go_Down(const std::string &data);
  void  go_Right(const std::string &data);
  void  go_Left(const std::string &data);

private:
  ECS::Entity   _entity;
  EventManager::Manager &_eventManager;
  ResourcesManager  &_resourcesManager;
  ECS::Manager      &_ecsManager;
};
