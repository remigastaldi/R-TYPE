#pragma once

#include <unordered_map>
#include <deque>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <boost/log/trivial.hpp>

namespace GameEngine
{
    namespace RessourceManager
    {
        enum FontType
        {
            REGULAR = 0,
            LIGHT,
            MEDIUM,
            BOLD,
            ITALIC
        };

        using FontInfo = std::tuple<std::string, std::string, FontType>;

        class Font
        {
          private:
            std::unordered_map<FontType, std::unordered_map<std::string, sf::Font *>> _fonts;
            std::unordered_map<FontType, std::unordered_map<std::string, std::string>> _indexPathFont;
            std::unordered_map<FontType, std::unordered_map<std::string, std::string>> _indexFontPath;

          public:
            Font() = default;

            bool addFont(const std::string &name, const std::string &path, FontType type = REGULAR)
            {
                if (_fonts[type].count(name) > 0) {
                    BOOST_LOG_TRIVIAL(error)
                        << "Font already exist " << name << " with this path " << _indexFontPath[type][name];
                    return false;
                }
                auto *f = new sf::Font();
                if (!f->loadFromFile(path)) {
                    BOOST_LOG_TRIVIAL(error) << "Error while trying to load font " << name << " path " << path;
                    return false;
                }

                _fonts[type][name] = f;
                _indexFontPath[type][name] = path;
                _indexPathFont[type][path] = name;

                return true;
            }

            const sf::Font &getFont(const std::string &name, FontType type = REGULAR)
            {
                if (_fonts[type].count(name) <= 0)
                    BOOST_LOG_TRIVIAL(error) << "Font " << name << " isnt loaded";
                else {
                    return *_fonts[type][name];
                }
                return *new sf::Font();
            }
        };

        class Sound
        {
          private:
            sf::SoundBuffer *errorBuffer = new sf::SoundBuffer();
            sf::Sound *errorSound = new sf::Sound();
            sf::Music *errorMusic = new sf::Music();

            std::unordered_map<std::string, sf::SoundBuffer> _sounds_buffer;
            std::unordered_map<std::string, sf::Sound> _sounds;
            std::unordered_map<std::string, sf::Music> _musics;

          public:
            void loadSound(const std::string &name, const std::string &path)
            {
                if (_sounds_buffer.count(name) != 0)
                    BOOST_LOG_TRIVIAL(error) << "Sound Buffer " << name << " already exist";
                if (!_sounds_buffer[name].loadFromFile(path))
                    BOOST_LOG_TRIVIAL(error) << "Cannot load sound " << path;
            }

            sf::SoundBuffer &getSoundBuffer(const std::string &name)
            {
                if (_sounds_buffer.count(name) == 0) {
                    BOOST_LOG_TRIVIAL(error) << "Sound Buffer " << name << " dont exist";
                    return *errorBuffer;
                }
                return _sounds_buffer[name];
            }

            void addSound(const std::string &name, const std::string &from)
            {
                if (_sounds.count(name) != 0) {
                    BOOST_LOG_TRIVIAL(error) << "Sound " << name << " already exist";
                    return;
                }

                if (_sounds_buffer.count(name) == 0) {
                    BOOST_LOG_TRIVIAL(error) << "Sound Buffer " << from << " dont exist";
                    return;
                }

                _sounds[name].setBuffer(_sounds_buffer[from]);
            }

            sf::Sound &getSound(const std::string &name)
            {
                if (_sounds.count(name) == 0) {
                    BOOST_LOG_TRIVIAL(error) << "Sound " << name << " dont exist";
                    return *errorSound;
                }
                return _sounds[name];
            }

            void loadMusic(const std::string &name, const std::string &path)
            {
                if (_musics.count(name) != 0) {
                    BOOST_LOG_TRIVIAL(error) << "Music " << name << " already exist";
                    return;
                }

                if (!_musics[name].openFromFile(path)) {
                    BOOST_LOG_TRIVIAL(error) << "Cant load music " << path;
                    return;
                }
            }

            sf::Music &getMusic(const std::string &name)
            {
                if (_musics.count(name) == 0) {
                    BOOST_LOG_TRIVIAL(error) << "Music " << name << " dont exist";
                    return *errorMusic;
                }
                return _musics[name];
            }
        };

        class Texture
        {
          private:
            sf::Texture *errorTexture = new sf::Texture();
            sf::Sprite *errorSprite = new sf::Sprite();

            std::unordered_map<std::string, sf::Texture> _textures;
            std::unordered_map<std::string, sf::Sprite> _sprites;
            std::deque<std::pair<std::string, std::string>> _delayedLoad;

          public:
            void delayedLoadTextureAdd(const std::string &name, const std::string &path)
            {
                _delayedLoad.emplace_back(name, path);
            }

            template <typename Fctor>
            void delayedLoadTextureRun(Fctor &&f)
            {
                size_t i = 0;
                size_t max = _delayedLoad.size();

                for (const auto &it : _delayedLoad) {
                    f(it.second, i, max);
                    loadTexture(it.first, it.second);
                    i += 1;
                }
                _delayedLoad.clear();
            }

            void loadTexture(const std::string &name, const std::string &path)
            {
                if (_textures.count(name) != 0) {
                    BOOST_LOG_TRIVIAL(error) << "Texture " << name << " already exist";
                    return;
                }
                if (!_textures[name].loadFromFile(path))
                    BOOST_LOG_TRIVIAL(error) << "Cannot load texture " << path;
            }

            void addSprite(const std::string &name, const std::string &from)
            {
                if (_sprites.count(name) != 0) {
                    BOOST_LOG_TRIVIAL(error) << "Sprite " << name << " already exist";
                    return;
                }

                if (_textures.count(from) == 0)
                    BOOST_LOG_TRIVIAL(error) << "Texture " << from << " dont exist";
                _sprites[name].setTexture(_textures[from]);
            }

            void addSprite(const std::string &name, const sf::Sprite &sprite)
            {
                if (_sprites.count(name) != 0)
                    BOOST_LOG_TRIVIAL(error) << "Sprite " << name << " already exist";
                _sprites[name] = sprite;
            }

            void addSprite(const std::string &name, const std::string &from, const sf::IntRect &location)
            {
                if (_sprites.count(name) != 0) {
                    BOOST_LOG_TRIVIAL(error) << "Sprite " << name << " already exist";
                    return;
                }

                if (_textures.count(from) == 0) {
                    BOOST_LOG_TRIVIAL(error) << "Texture " << from << " dont exist";
                    return;
                }

                _sprites[name].setTexture(_textures[from]);
                _sprites[name].setTextureRect(location);
            }

            sf::Texture &getTexture(const std::string &name)
            {
                if (_textures.count(name) == 0) {
                    BOOST_LOG_TRIVIAL(error) << "Texture " << name << " dont exist";
                    return *errorTexture;
                }
                return _textures[name];
            }

            sf::Sprite &getSprite(const std::string &name)
            {
                if (_sprites.count(name) == 0) {
                    BOOST_LOG_TRIVIAL(error) << "Sprite " << name << " dont exist";
                    return *errorSprite;
                }
                return _sprites[name];
            }
        };

        struct Manager
        {
            Texture texture;
            Font font;
            Sound sound;
        };
    }
}