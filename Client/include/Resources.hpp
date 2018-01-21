/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-16T21:10:22+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-20T22:53:49+01:00
 */


#pragma once

#include  "ResourcesManager.hpp"
#include  <SFML/Graphics/Font.hpp>
#include  <SFML/Audio.hpp>
#include  <SFML/Graphics/Texture.hpp>
#include  <SFML/Graphics/Sprite.hpp>

class Texture : public Resource<sf::Texture>
{
public:
  explicit  Texture(const std::string &name)
    : Resource(name)
    {
      // _resource.loadFromFile(name);
    }

    Texture(const std::string &name, const sf::Texture &texture)
      : Resource(name, texture)
    {}

    void  loadFromFile(void)
    {
      _resource.loadFromFile(_name);
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
  {
    // _resource.loadFromFile(name);
  }

  SoundBuffer(const std::string &name, const sf::SoundBuffer &soundBuffer)
    : Resource(name, soundBuffer)
  {}

  void  loadFromFile(void)
  {
    _resource.loadFromFile(_name);
  }

  typedef sf::SoundBuffer ContentType;
};

class Music : public Resource<sf::Music>
{
public:
  explicit  Music(const std::string &name)
    : Resource(name)
  {
    // _resource.openFromFile(name);
  }

  void  loadFromFile(void)
  {
    _resource.openFromFile(_name);
  }

  typedef sf::Music ContentType;
};


class Font : public Resource<sf::Font>
{
public:
  explicit Font(const std::string &name)
    : Resource(name)
    {
      // _resource.loadFromFile(name);
    }

    Font(const std::string &name, const sf::Font &font)
      : Resource(name, font)
    {}

    void  loadFromFile(void)
    {
      _resource.loadFromFile(_name);
    }

  typedef sf::Font ContentType;
};
