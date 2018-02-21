#pragma once

#include <AlfredBase/Utils/NonCopyable.hpp>
#include <unordered_map>
#include <ostream>
#include <stack>
#include "LibraryInterfaces/IScene.hpp"

namespace GameEngine
{
  class SceneManager : Alfred::Utils::NonCopyable
  {
    private:
      std::unordered_map<std::string, IScene *> _scenes;
      std::stack<IScene *> _scenesList;

    public:
      SceneManager() :
        _scenes(),
        _scenesList()
      {
      };

      template <typename S, typename ...Args>
      void addScene(const std::string &name, Args &&...args)
      {
        if (_scenes.count(name) > 0)
          LOG_ERROR << "Scene already exist" << std::endl;
        else {
          _scenes[name] = new S(std::forward<Args>(args)...);
          LOG_SUCCESS << "Scene " << name << " loaded" << std::endl;
        }
      };

      void deleteScene(const std::string &name)
      {
        if (_scenes.erase(name) == 0)
          LOG_ERROR << "Scene " << name << " doesnt exist while erasing it";
        else
          LOG_ERROR << "Scene " << name << " deleted" << std::endl;
      }

      const std::unordered_map<std::string, IScene *> &listScenes() const
      {
        return _scenes;
      };

      void pushScene(const std::string &name)
      {
        if (_scenes.count(name) == 0) {
          LOG_ERROR << "Scene " << name << " doesn't exist" << std::endl;
          return;
        }

        if (_scenesList.empty()) {
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
        if (!_scenesList.empty())
          _scenesList.top()->onEnter();
      }

      void update(const float time, GameEngine::GameManagers &manager)
      {
        _scenesList.top()->update(time, manager);
      }

      IScene *operator[](const std::string &name)
      {
        if (_scenes.count(name) == 0) {
          LOG_ERROR << "Scene dont exist" << std::endl;
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
