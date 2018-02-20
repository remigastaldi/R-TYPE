/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-20T20:45:23+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-20T17:55:30+01:00
 */


#include  "Ship.hpp"
#include <iostream>

Ship::Ship(GameEngine::GameManagers &gameManagers, MapEngine &mapEngine)
  : _gameManagers(gameManagers),
    _mapEngine(mapEngine),
    _entity(_gameManagers.ecs.createEntity()),
    _fireTickCounter(0),
    _fire(false),
    _spriteName(),
    _activeKeys()
  {
    std::shared_ptr<Texture> texture = _gameManagers.resources.get<Texture>("player_ship_texture");

    std::cout << "Ship ID is : " << _entity << std::endl;

    _spriteName = "player_sprite[" + std::to_string(_entity) + "]";
    Sprite sprite(_spriteName, *texture);
    sprite.getContent().setRotation(90);
    sprite.getContent().setTextureRect(sf::IntRect(0, 0, 160, 160));
    sprite.getContent().setScale(0.5, 0.5);

    _gameManagers.resources.addResource<Sprite>(_spriteName, sprite);


    _gameManagers.ecs.addComponent<ECS::Components::Player>(_entity, ECS::Components::Player("Remi"));
    _gameManagers.ecs.addComponent<ECS::Components::Position>(_entity, ECS::Components::Position(200, 400));
    _gameManagers.ecs.addComponent<ECS::Components::Collisionable>(_entity, ECS::Components::Collisionable(_entity, ECS::Components::Collisionable::Type::ALLY));
    _gameManagers.ecs.addComponent<ECS::Components::Drawable>(_entity, ECS::Components::Drawable(_spriteName));
    _gameManagers.ecs.addComponent<ECS::Components::Direction>(_entity, ECS::Components::Direction(0, 0, 7));
    _gameManagers.ecs.addComponent<ECS::Components::Health>(_entity, ECS::Components::Health(100));


    _gameManagers.ecs.updateEntityToSystems(_entity);

    _gameManagers.event.addEvent<void, const std::string &>("SpaceKeyEvent");

    _gameManagers.event.listen<void, sf::Event>("KeyPressedEvent", [&](sf::Event event) { this->keyPressed(event);});
    _gameManagers.event.listen<void, sf::Event>("KeyReleasedEvent", [&](sf::Event event) { this->keyRelease(event);});
    _gameManagers.event.listen<void, const std::string &>("SpaceKeyEvent", [&](const std::string & msg) { this->fire(msg);});

    _gameManagers.sound.loadSound("shoot", "../../Client/media/sounds/shoot.wav");
    _gameManagers.sound.registerSoundWithEvent<void, sf::Event>("shoot", "SpaceKeyEvent");

    _gameManagers.event.listen<void, ECS::Entity>("UnitOutOfSpace", [&](ECS::Entity e) -> void {
      _gameManagers.ecs.destroyEntity(e);
    });
  }

void  Ship::keyPressed(sf::Event event)
{
  std::shared_ptr<ECS::Components::Direction> direction = _gameManagers.ecs.getComponent<ECS::Components::Direction>(_entity);

  std::shared_ptr<ECS::Components::Position> position = _gameManagers.ecs.getComponent<ECS::Components::Position>(_entity);

  _activeKeys[event.key.code] = true;
  switch (event.key.code)
  {
  case sf::Keyboard::Key::Up :
    direction->yDirection = -1;
    break;
  case sf::Keyboard::Key::Down :
    direction->yDirection = 1;
    break;
  case sf::Keyboard::Key::Right :
    direction->xDirection = 1;
    break;
  case sf::Keyboard::Key::Left :
    direction->xDirection = -1;
    break;
  case sf::Keyboard::Key::Space :
    _fire = true;
    break;
  default :
    break;
  }
}


void  Ship::keyRelease(sf::Event event)
{
  std::shared_ptr<ECS::Components::Direction> direction = _gameManagers.ecs.getComponent<ECS::Components::Direction>(_entity);

  _activeKeys[event.key.code] = false;
  switch (event.key.code)
  {
  case sf::Keyboard::Key::Up :
    if (_activeKeys[sf::Keyboard::Key::Down])
      direction->yDirection = -1;
    else
      direction->yDirection = 0;
    break;

  case sf::Keyboard::Key::Down :
    if (_activeKeys[sf::Keyboard::Key::Up])
      direction->yDirection = 1;
    else
      direction->yDirection = 0;
    break;

  case sf::Keyboard::Key::Right :
    if (_activeKeys[sf::Keyboard::Key::Left])
      direction->xDirection = -1;
    else
      direction->xDirection = 0;
    break;

  case sf::Keyboard::Key::Left :
    if (_activeKeys[sf::Keyboard::Key::Right])
      direction->xDirection = 1;
    else
      direction->xDirection = 0;
    break;

  case sf::Keyboard::Key::Space :
    _fire = false;

  default :
    break;
  }
}

void  Ship::fire(const std::string &msg)
{
  (void) msg;

  ECS::Entity e = _gameManagers.ecs.createEntity();

  std::shared_ptr<ECS::Components::Position> position = _gameManagers.ecs.getComponent<ECS::Components::Position>(_entity);

  std::shared_ptr<Texture>  texture(_gameManagers.resources.get<Texture>("player_missiles_texture"));
  std::string spriteName = "player_missiles[" + std::to_string(e) + "]";
  Sprite sprite(spriteName, *texture);
  _gameManagers.resources.addResource<Sprite>(spriteName, sprite);

	sf::Sprite &spriteMissiles = _gameManagers.resources.getContent<Sprite>(spriteName);
	spriteMissiles.setRotation(-90);
	spriteMissiles.setTextureRect(sf::IntRect(0, 0, 30, 112));

  _gameManagers.ecs.addComponent<ECS::Components::Position>(e, ECS::Components::Position(position->x, position->y + 60));
  _gameManagers.ecs.addComponent<ECS::Components::Collisionable>(e, ECS::Components::Collisionable(e, ECS::Components::Collisionable::Type::MISSILE));
  _gameManagers.ecs.addComponent<ECS::Components::Drawable>(e, ECS::Components::Drawable(spriteName));
  _gameManagers.ecs.addComponent<ECS::Components::Direction>(e, ECS::Components::Direction(1, 0, 30));
  _gameManagers.ecs.addComponent<ECS::Components::Damages>(e, ECS::Components::Damages(1));
  _gameManagers.ecs.updateEntityToSystems(e);
}


void  Ship::update(void )
{

   if (_fire && _fireTickCounter == 0)
  {
    _fireTickCounter++;
    _gameManagers.event.fire<void, const std::string &>("SpaceKeyEvent", "Fire");
  }
  else if (_fire && _fireTickCounter > 20)
    _fireTickCounter = 0;
  else if (_fire)
    _fireTickCounter++;
  else
    _fireTickCounter = 0;
}


ECS::Entity Ship::getID(void) const
{
  return (_entity);
}
