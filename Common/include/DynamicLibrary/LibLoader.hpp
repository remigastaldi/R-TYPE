/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-02-16T14:10:00+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-19T14:31:34+01:00
 */


#pragma once

#ifdef WIN32
#include <windows.h>
#include "mon_dirent.hpp"
#else

#include <dlfcn.h>
#include <dirent.h>

#endif

#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
#include "FindOS.hpp"
#include <AlfredBase/Utils/NonCopyable.hpp>
#include <unordered_map>
#include "DynamicLibrary/DynamicLibraryTypes.hpp"
#include "Logger/Logger.hpp"
#include "ECS/Manager.hpp"
#include "ECS/Component.hpp"
#include <type_traits>
#include <GameManagers.hpp>
#include <stdio.h>

namespace GameEngine
{
  struct GameManagers;
}

class MapEngine;

class IAttack;

class IMap;

class IMob;

class IMove;

class IPart;

class IPowerUp;

class IRessources;

class IScene;

class IShipBluprint;

class LibLoader;

namespace EventManager
{
  class Manager;
}

#ifdef WIN32

typedef char const * (*getNameOfLib)();

typedef IAttack *(*getAttackSymbol)(GameEngine::GameManagers &gameManagers, MapEngine &mapEngine, ECS::Entity);
typedef IMap *(*getMapSymbol)(GameEngine::GameManagers &gameManagers);
typedef IMob *(*getMobSymbol)(GameEngine::GameManagers &gameManagers, MapEngine &mapEngine, ECS::Components::Position);
typedef IMove *(*getMoveSymbol)(GameEngine::GameManagers &gameManagers, ECS::Entity, int direction, int speed);
typedef IPart *(*getPartSymbol)();
typedef IPowerUp *(*getPowerUpSymbol)();
typedef IRessources *(*getRessourceSymbol)(GameEngine::GameManagers &gameManagers);
typedef IScene *(*getSceneSymbol)();
typedef IShipBluprint *(*getShipBlueprintSymbol)();

#else

typedef char const *(*getNameOfLib)();

typedef IAttack *(*getAttackSymbol)(GameEngine::GameManagers &gameManagers, MapEngine &mapEngine, ECS::Entity);
typedef IMap *(*getMapSymbol)(GameEngine::GameManagers &gameManagers);
typedef IMob *(*getMobSymbol)(GameEngine::GameManagers &gameManagers, MapEngine &mapEngine, ECS::Components::Position);
typedef IMove *(*getMoveSymbol)(GameEngine::GameManagers &gameManagers, ECS::Entity, int direction, int speed);
typedef IPart *(*getPartSymbol)();
typedef IPowerUp *(*getPowerUpSymbol)();
typedef void (*getRessourceSymbol)(GameEngine::GameManagers &);
typedef IScene *(*getSceneSymbol)();
typedef IShipBluprint *(*getShipBlueprintSymbol)();

#endif

static std::string getOSDynLibExtension()
{
  if constexpr (the_os == OS::Linux)
    return ".so";
  else if constexpr (the_os == OS::Mac)
    return ".dylib";
  else
    return ".dll";
}

template <typename T, typename HELPER>
class __lib__implem : public Alfred::Utils::NonCopyable
{
  private:
    std::string _osLibEnding;
    //map of file path, file names / bool (is visible), handler
    std::unordered_map<std::string, std::unordered_map<std::string, T>> _files;
    std::unordered_map<std::string, T> _symbols;

  private:

    std::string getLibName(const std::string &path)
    {
#ifdef WIN32
      HINSTANCE hGetProcIDDLL = LoadLibrary(path.c_str());
      if (!hGetProcIDDLL) {
          LOG_ERROR << "could not load the dynamic library" << std::endl;
          return nullptr;
      }

    getNameOfLib tmp = (getNameOfLib)(GetProcAddress(hGetProcIDDLL, "getName"));
    if (tmp == NULL)
    {
      LOG_ERROR << "Failed to load lib" << GetLastError() << " " << path << std::endl;
      return "";
    }

      return tmp();
#else
      void *handle = dlopen(path.c_str(), RTLD_LAZY);
      char *lError = dlerror();
      if (lError) {
        LOG_ERROR << "Error while loading lib name " << path << " " << lError << std::endl;
        return "";
      }
      return (((getNameOfLib)(dlsym(handle, "getName")))());
#endif
    }

    T getSymbol(const std::string &path)
    {
#ifdef WIN32
      HINSTANCE hGetProcIDDLL = LoadLibrary(path.c_str());
      if (!hGetProcIDDLL) {
          LOG_ERROR << "could not load the dynamic library" << std::endl;
          return nullptr;
      }

      T tmp = (T) GetProcAddress(hGetProcIDDLL, "getSymbol");
      if (tmp == NULL)
      {
            LOG_ERROR << "Failed to load lib" << GetLastError() << " " << path << std::endl;
            return nullptr;
      }
      return tmp;
#else
      void *handle = dlopen(path.c_str(), RTLD_LAZY);
      char *lError = dlerror();
      if (lError) {
        LOG_ERROR << "Error while loading lib symbol " << path << " " << lError << std::endl;
        return nullptr;
      }
      return (T)(dlsym(handle, "getSymbol"));
#endif
    }

  public:
    /**
     * @brief Ctor
     */
    __lib__implem() :
      _osLibEnding(getOSDynLibExtension()),
      _files(),
      _symbols()
    {}

    /**
     * @brief Update
     * @return
     */

    std::vector<std::pair<std::string, T>> update()
    {
      struct dirent *entry;
      DIR *dp;

      std::vector<std::pair<std::string, T>> out;
      for (auto &it : _files) {
        dp = opendir(it.first.c_str());
        if (dp == NULL) {
          LOG_ERROR << "Can't open dir " << it.first << std::endl;
          continue;
        }

        LOG_WARNING << "Updating " << it.first << std::endl;

        while ((entry = readdir(dp))) {
          std::string tmpPath(entry->d_name);

          if (tmpPath == "." || tmpPath == "..")
            continue;

          std::string curPath = it.first + tmpPath;

          if (curPath.find(_osLibEnding) != 0) {
            if (it.second.count(curPath) <= 0) {
              //Get name

              LOG_INFO << "Trying to load lib " << curPath << std::endl;

              std::string nameOfLib = getLibName(curPath);

              if (nameOfLib.empty())
                LOG_ERROR << "Error while loading lib " << curPath << std::endl;
              else {
                //Load lib
                T curSymbol = getSymbol(curPath);

                LOG_INFO << "Loading library: " << nameOfLib << std::endl;

                if (curSymbol == nullptr)
                  LOG_ERROR << "Failed to load lib " << nameOfLib << " at path" << curPath << std::endl;
                else {
                  LOG_SUCCESS << "Successfully loaded lib " << nameOfLib << " at path " << curPath << std::endl;
                  //Add to path / symbol

                  it.second[curPath] = curSymbol;

                  //Add to symbol map
                  if (_symbols.count(nameOfLib) > 0)
                    LOG_ERROR << "Lib with name " << nameOfLib << " already exist" << std::endl;
                  else
                    _symbols[nameOfLib] = curSymbol;

                  //Add to ret
                  out.push_back(std::make_pair(nameOfLib, curSymbol));
                }
              }
            }
          }
        }
      }
      return out;
    };

    /**
     * @brief Add folder
     * @param path
     * @param toRefresh
     * @return
     */
    bool addFolder(const std::string &path)
    {
      _files[path] = std::unordered_map<std::string, T>();
      return true;
    }

    T get(const std::string &name)
    {
      if (_symbols.count(name) <= 0) {
        LOG_ERROR << "Cant find lib " << name << std::endl;
        return nullptr;
      }
      return _symbols[name];
    }

    std::vector<std::string> getAll()
    {
      std::vector<std::string> out;
      for (const auto &it : _symbols)
        out.push_back(it.first);

      return out;
    }

    void set(const std::string &name, T func)
    {
      _symbols[name] = func;
    }
};

class LibLoader
{
  public:
    __lib__implem<getAttackSymbol, IAttack> attack;
    __lib__implem<getMapSymbol, IMap> map;
    __lib__implem<getMobSymbol, IMob> mob;
    __lib__implem<getMoveSymbol, IMove> move;
    __lib__implem<getPartSymbol, IPart> part;
    __lib__implem<getPowerUpSymbol, IPowerUp> powerup;
    __lib__implem<getRessourceSymbol, IRessources> ressource;
    __lib__implem<getSceneSymbol, IScene> scene;
    __lib__implem<getShipBlueprintSymbol, IShipBluprint> ship_blueprint;

  public:
    LibLoader() :
      attack(),
      map(),
      mob(),
      move(),
      part(),
      powerup(),
      ressource(),
      scene(),
      ship_blueprint()
    {};

    ~LibLoader() = default;

    void updateAll()
    {
      LOG_INFO << "Updating lib loader" << std::endl;
      attack.update();
      map.update();
      mob.update();
      move.update();
      part.update();
      powerup.update();
      ressource.update();
      scene.update();
      ship_blueprint.update();
    }

    void updateAllRessources(GameEngine::GameManagers &manager)
    {
      for (const auto &it: ressource.getAll())
        ressource.get(it)(manager);
    }
};
