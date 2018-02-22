/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-20T20:45:49+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-21T01:10:49+01:00
 */


#pragma once

#include  "IEntityObject.hpp"

#include  "GameManagers.hpp"
#include  "MapEngine.hpp"
#include  "EventManager.hpp"
#include  "ECS/Manager.hpp"

#include  "Resources.hpp"
#include  "ECS/Components/Components.hpp"

#include  <SFML/System.hpp>
#include  <SFML/Graphics.hpp>

class Ship : public IEntityObject
{
public:
  explicit Ship(GameEngine::GameManagers &gameManager, MapEngine &mapEngine);

  ~Ship();

  void  keyPressed(sf::Event);
  void  keyRelease(sf::Event);
  void  fire(const std::string &);
  void  update(void);
  ECS::Entity   getID(void) const;

private:
  GameEngine::GameManagers &_gameManagers;
  MapEngine &_mapEngine;
  ECS::Entity   _entity;
  std::unordered_map<std::string, EventManager::EventListener>  _listeners;

  int  _fireTickCounter;
  bool _fire;

  std::string _spriteName;

  std::unordered_map<sf::Keyboard::Key, bool> _activeKeys;
};
