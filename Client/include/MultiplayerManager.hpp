#include <AlfredBase/Utils/MakeFinal.hpp>
#include <AlfredBase/Utils/NonCopyable.hpp>

#pragma once

#include <unordered_map>
#include <ECS/Entity.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <ECS/Manager.hpp>
#include <EventManager.hpp>
#include <ECS/Components/Components.hpp>
#include <ECS/Components/Stats.hpp>
#include "Resources.hpp"

class MultiplayerManager : Alfred::Utils::MakeFinal<MultiplayerManager>, public Alfred::Utils::NonCopyable
{
  private:
    std::unordered_map<std::string, ECS::Entity> _players;
    std::string _playerName;
    ECS::Entity _playerID; //Useless ?
    ECS::Manager &_ecs;
    EventManager::Manager &_event;
    ResourcesManager &_ressources;

    //TODO give ECS

  public:
    explicit MultiplayerManager(ECS::Manager &ecs, EventManager::Manager &event, ResourcesManager &ressources) :
      _players(),
      _playerName(),
      _playerID(),
      _ecs(ecs),
      _event(event),
      _ressources(ressources)
    {
      _event.listen<int, std::string>("multiplayer go up", [&](std::string id) {
        up(id);
        return 0;
      });
      _event.listen<int, std::string>("multiplayer go down", [&](std::string id) {
        down(id);
        return 0;
      });
      _event.listen<int, std::string>("multiplayer go left", [&](std::string id) {
        left(id);
        return 0;
      });
      _event.listen<int, std::string>("multiplayer go right", [&](std::string id) {
        right(id);
        return 0;
      });
      _event.listen<int, std::string>("multiplayer release up", [&](std::string id) {
        release_up(id);
        return 0;
      });
      _event.listen<int, std::string>("multiplayer release down", [&](std::string id) {
        release_down(id);
        return 0;
      });
      _event.listen<int, std::string>("multiplayer release left", [&](std::string id) {
        release_left(id);
        return 0;
      });
      _event.listen<int, std::string>("multiplayer release right", [&](std::string id) {
        release_right(id);
        return 0;
      });
      _event.listen<int, std::string>("multiplayer shoot", [&](std::string id) {
        shoot(id);
        return 0;
      });
      _event.listen<int, std::string>("multiplayer join", [&](std::string id) {
        join(id);
        return 0;
      });
      _event.listen<int, std::string>("multiplayer disconnect", [&](std::string id) {
        disconnect(id);
        return 0;
      });
      _event.listen<int, std::string>("multiplayer setPlayerName", [&](std::string id) {
        setPlayerName(id);
        return 0;
      });
    };

    void up(const std::string &id)
    {
      if (id == _playerName || _players.count(id) <= 0)
        return;

      _ecs.getComponent<ECS::Components::Direction>(_players[id])->yDirection = -1;
    }

    void down(const std::string &id)
    {
      if (id == _playerName || _players.count(id) <= 0)
        return;

      _ecs.getComponent<ECS::Components::Direction>(_players[id])->yDirection = 1;
    }

    void left(const std::string &id)
    {
      if (id == _playerName || _players.count(id) <= 0)
        return;

      _ecs.getComponent<ECS::Components::Direction>(_players[id])->xDirection = -1;
    }

    void right(const std::string &id)
    {
      if (id == _playerName || _players.count(id) <= 0)
        return;

      _ecs.getComponent<ECS::Components::Direction>(_players[id])->xDirection = 1;
    }

    void release_up(const std::string &id)
    {
      if (id == _playerName || _players.count(id) <= 0)
        return;

      _ecs.getComponent<ECS::Components::Direction>(_players[id])->yDirection = 0;
    }

    void release_down(const std::string &id)
    {
      if (id == _playerName || _players.count(id) <= 0)
        return;

      _ecs.getComponent<ECS::Components::Direction>(_players[id])->yDirection = 0;
    }

    void release_left(const std::string &id)
    {
      if (id == _playerName || _players.count(id) <= 0)
        return;

      _ecs.getComponent<ECS::Components::Direction>(_players[id])->xDirection = 0;
    }

    void release_right(const std::string &id)
    {
      if (id == _playerName || _players.count(id) <= 0)
        return;

      _ecs.getComponent<ECS::Components::Direction>(_players[id])->xDirection = 0;
    }

    void shoot(const std::string &id)
    {
      if (id == _playerName || _players.count(id) <= 0)
        return;

      ECS::Entity e = _ecs.createEntity();

      std::shared_ptr<ECS::Components::Position> position = _ecs.getComponent<ECS::Components::Position>(_players[id]);

      std::shared_ptr<Texture> texture(
        _ressources.load<Texture>("player_missiles_texture", "../../Client/media/img/ship/allies/playersMissiles.png"));
      std::string spriteName = "player_missiles[" + std::to_string(e) + "]";
      Sprite sprite(spriteName, *texture);
      _ressources.addResource<Sprite>(spriteName, sprite);

      sf::Sprite &spriteMissiles = _ressources.getContent<Sprite>(spriteName);
      spriteMissiles.setRotation(-90);
      spriteMissiles.setTextureRect(sf::IntRect(0, 0, 30, 112));

      _ecs.addComponent<ECS::Components::Position>(e, ECS::Components::Position(position->x, position->y + 60));
      _ecs.addComponent<ECS::Components::Collisionable>(e, ECS::Components::Collisionable(e,
                                                                                          ECS::Components::Collisionable::Type::ALLY));
      _ecs.addComponent<ECS::Components::Drawable>(e, ECS::Components::Drawable(spriteName));
      _ecs.addComponent<ECS::Components::Direction>(e, ECS::Components::Direction(1, 0, 30));
      _ecs.updateEntityToSystems(e);
    }

    void disconnect(const std::string &id)
    {
      if (id == _playerName || _players.count(id) <= 0)
        return;
      _ecs.destroyEntity(_players[id]);
    }

    void join(const std::string &id)
    {
      std::shared_ptr<Texture> texture = _ressources.load<Texture>("metallos_texture",
                                                                   "../../Client/media/img/ship/enemies/CX16-X2.png");
      std::string spriteName = "metallos_sprite[" + id + "]";
      Sprite sprite(spriteName, *texture);
      _ressources.addResource<Sprite>(spriteName, sprite);

      _players[id] = _ecs.createEntity();

      _ecs.addComponent<ECS::Components::Player>(_players[id], ECS::Components::Player(id));
      _ecs.addComponent<ECS::Components::Position>(_players[id], ECS::Components::Position(200, 200));
      _ecs.addComponent<ECS::Components::Drawable>(_players[id], ECS::Components::Drawable(spriteName));
      _ecs.addComponent<ECS::Components::Direction>(_players[id], ECS::Components::Direction(0, 0, 10));
      _ecs.addComponent<ECS::Components::Collisionable>(_players[id], ECS::Components::Collisionable(_players[id],
                                                                                                     ECS::Components::Collisionable::Type::ALLY_MISSILE));

      _ecs.updateEntityToSystems(_players[id]);
    }

    void setPlayerName(const std::string &id)
    {
      _playerName = id;
    }
};