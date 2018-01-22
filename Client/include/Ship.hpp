/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-20T20:45:49+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-21T23:07:14+01:00
 */


#pragma once

#include  "GameManagers.hpp"

#include  "EventManager.hpp"
#include  "ECS/Manager.hpp"

#include  "Resources.hpp"
#include  "ECS/Components/Components.hpp"

#include  <SFML/System.hpp>
#include  <SFML/Graphics.hpp>

class Ship
{
public:
  explicit Ship(GameEngine::GameManagers &gameManager);

  ~Ship() {};

  void  keyPressed(sf::Event);
  void  keyRelease(sf::Event);
  void  fire(const std::string &);
  void  update(void);

private:
  GameEngine::GameManagers _gameManagers;
  ECS::Entity   _entity;

  int  _fireTickCounter;
  bool _fire;
};
