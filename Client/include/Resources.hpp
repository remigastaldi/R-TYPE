/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-16T21:10:22+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-17T01:33:58+01:00
 */


#pragma once

#include  "ResourcesManager.hpp"
#include  <SFML/Graphics/Font.hpp>
#include  <SFML/Audio.hpp>
#include  <SFML/Graphics/Texture.hpp>
#include  <SFML/Graphics/Sprite.hpp>

class Texture : public Resource
{
public:
  explicit  Texture(const std::string &name)
    : Resource(name),
      _texture()
    {
      _texture.loadFromFile(name);
    }

  sf::Texture &getContent(void)
  {
    return (_texture);
  }

  void  setSmooth(bool val)
  {
    _texture.setSmooth(val);
  }

private:
  sf::Texture _texture;
};


class SoundBuffer : public Resource
{
public:
  explicit  SoundBuffer(const std::string &name)
    : Resource(name),
    _soundBuffer()
  {
    _soundBuffer.loadFromFile(name);
  }

  sf::SoundBuffer &getContent(void)
  {
    return (_soundBuffer);
  }
private:
  sf::SoundBuffer _soundBuffer;
};

class Music : public Resource
{
public:
  explicit  Music(const std::string &name)
    : Resource(name),
      _music()
  {
    _music.openFromFile(name);
  }

  sf::Music &getContent(void)
  {
    return (_music);
  }
private:
  sf::Music _music;
};


class Font : public Resource
{
public:
  explicit Font(const std::string &name)
    : Resource(name),
      _font()
    {
      _font.loadFromFile(name);
    }

    sf::Font  &getContent(void)
    {
      return (_font);
    }
private:
  sf::Font  _font;
};
