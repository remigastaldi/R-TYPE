/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-20T20:45:49+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-21T18:02:55+01:00
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


  void  keyPressed(sf::Event);
  void  keyRelease(sf::Event);
  void  fire(sf::Event event);

private:
  ECS::Entity   _entity;
  EventManager::Manager &_eventManager;
  ResourcesManager  &_resourcesManager;
  ECS::Manager      &_ecsManager;
};
