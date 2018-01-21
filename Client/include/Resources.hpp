/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-16T21:10:22+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-21T07:10:56+01:00
 */


#pragma once

#include  "ResourcesManager.hpp"
#include  <SFML/Graphics/Font.hpp>
#include  <SFML/Audio.hpp>
#include  <SFML/Graphics/Texture.hpp>
#include  <SFML/Graphics/Sprite.hpp>

class Sprite : public Resource<sf::Sprite>
{
public:
  explicit  Sprite(const std::string &name)
    : Resource(name),
    _texture()
    {}

    Sprite(const std::string &name, const sf::Sprite &texture)
      : Resource(name, texture),
    _texture()
    {}

    void  loadFromFile(const std::string &path)
    {
      _texture.loadFromFile(path);
      _resource.setTexture(_texture);
    }

    typedef sf::Sprite ContentType;

  private:
    sf::Texture _texture;
};

class Texture : public Resource<sf::Texture>
{
public:
  explicit  Texture(const std::string &name)
    : Resource(name)
    {}

    Texture(const std::string &name, const sf::Texture &texture)
      : Resource(name, texture)
    {}

    void  loadFromFile(const std::string &path)
    {
      _resource.loadFromFile(path);
    }

    void setSmooth(bool val)
    {
      _resource.setSmooth(val);
    }

    typedef sf::Texture ContentType;
};


class SoundBuffer : public Resource<sf::SoundBuffer>
{
public:
  explicit  SoundBuffer(const std::string &name)
    : Resource(name)
  {}

  SoundBuffer(const std::string &name, const sf::SoundBuffer &soundBuffer)
    : Resource(name, soundBuffer)
  {}

  void  loadFromFile(const std::string &path)
  {
    _resource.loadFromFile(path);
  }

  typedef sf::SoundBuffer ContentType;
};

class Music : public Resource<sf::Music>
{
public:
  explicit  Music(const std::string &name)
    : Resource(name)
  {}

  void  loadFromFile(const std::string &path)
  {
    _resource.openFromFile(path);
  }

  typedef sf::Music ContentType;
};


class Font : public Resource<sf::Font>
{
public:
  explicit Font(const std::string &name)
    : Resource(name)
    {}

    Font(const std::string &name, const sf::Font &font)
      : Resource(name, font)
    {}

    void  loadFromFile(const std::string &path)
    {
      _resource.loadFromFile(path);
    }

  typedef sf::Font ContentType;
};
