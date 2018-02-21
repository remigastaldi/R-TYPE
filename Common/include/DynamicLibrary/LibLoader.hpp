/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-02-16T14:10:00+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-19T14:31:34+01:00
 */


#pragma once

#ifdef WIN32
#include <windows.h>
#else

#include <dlfcn.h>

#endif

#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
#include "FindOS.hpp"
#include <experimental/filesystem>
#include <AlfredBase/Utils/NonCopyable.hpp>
#include <unordered_map>
#include "DynamicLibrary/DynamicLibraryTypes.hpp"
#include "Logger/Logger.hpp"
#include "ECS/Manager.hpp"
#include "ECS/Component.hpp"
#include <type_traits>
#include <GameManagers.hpp>

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

typedef char const * (__stdcall *getNameOfLib)();

typedef IAttack *(__stdcall *getAttackSymbol)(GameEngine::GameManagers &gameManagers, MapEngine &mapEngine, ECS::Entity);
typedef IMap *(__stdcall *getMapSymbol)(GameEngine::GameManagers &gameManagers);
typedef IMob *(__stdcall *getMobSymbol)(GameEngine::GameManagers &gameManagers, MapEngine &mapEngine, ECS::Components::Position);
typedef IMove *(__stdcall *getMoveSymbol)(GameEngine::GameManagers &gameManagers, ECS::Entity, int direction, int speed);
typedef IPart *(__stdcall *getPartSymbol)();
typedef IPowerUp *(__stdcall *getPowerUpSymbol)();
typedef void (__stdcall *getRessourceSymbol)(GameEngine::GameManagers &);
typedef IScene *(__stdcall *getSceneSymbol)();
typedef IShipBluprint *(__stdcall *getShipBlueprintSymbol)();

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
      LOG_ERROR << "Failed to load lib" << GetLastError() << " " << path << << std::endl;
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
            LOG_ERROR << "Failed to load lib" << GetLastError() << " " << path << << std::endl;
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
      std::vector<std::pair<std::string, T>> out;
      for (auto &it : _files) {
        LOG_INFO << "Updating " << it.first << std::endl;
        for (auto &p: std::experimental::filesystem::directory_iterator(it.first)) {
          std::string curPath = p.path().generic_string();
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
      std::experimental::filesystem::directory_entry entry(path);
      if (std::experimental::filesystem::exists(entry)) {
        _files[path] = std::unordered_map<std::string, T>();
        return true;
      }
      LOG_ERROR << "Directory " << path << " not exist" << std::endl;
      return false;
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
