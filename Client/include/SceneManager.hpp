#pragma once

#include <AlfredBase/Utils/NonCopyable.hpp>
#include <unordered_map>
#include <boost/log/trivial.hpp>
#include <ostream>
#include <stack>
#include "Common/LibraryInterfaces/IScene.hpp"

namespace GameEngine
{
    class SceneManager : Alfred::Utils::NonCopyable
    {
      private:
        std::unordered_map<std::string, IScene *> _scenes;
        std::stack<IScene *> _scenesList;

      public:
        SceneManager() = default;

        template <typename S, typename ...Args>
        void addScene(const std::string &name, Args ...args)
        {
            if (_scenes.count(name) > 0)
                BOOST_LOG_TRIVIAL(error) << "Scene already exist";
            else
            {
                _scenes[name] = new S(args...);
                BOOST_LOG_TRIVIAL(info) << "Scene " << name << " loaded";
            }
        };

        void deleteScene(const std::string &name)
        {
            if (_scenes.erase(name) == 0)
                BOOST_LOG_TRIVIAL(error) << "Scene " << name << " doesnt exist while erasing it";
            else
                BOOST_LOG_TRIVIAL(error) << "Scene " << name << " deleted";
        }

        const std::unordered_map<std::string, IScene *> &listScenes() const
        {
            return _scenes;
        };

        void pushScene(const std::string &name)
        {
            if (_scenes.count(name) == 0)
            {
                BOOST_LOG_TRIVIAL(error) << "Scene dont exist";
                return;
            }

            if (_scenesList.empty())
            {
                _scenesList.push(_scenes[name]);
                _scenesList.top()->onEnter();
                return;
            }

            _scenesList.top()->onExit();
            _scenesList.push(_scenes[name]);
            _scenesList.top()->onEnter();
        }

        void popScene()
        {
            if (_scenesList.empty())
                return;

            _scenesList.top()->onExit();
            _scenesList.pop();
            _scenesList.top()->onEnter();
        }

        IScene *operator[](const std::string &name)
        {
            if (_scenes.count(name) == 0)
            {
                BOOST_LOG_TRIVIAL(error) << "Scene dont exist";
                return nullptr;
            }
            return _scenes[name];
        }

        std::ostream &operator<<(std::ostream &os)
        {
            for (const auto &it : _scenes)
                os << it.first << std::endl;
            return os;
        }
    };
}

