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

typedef std::string (__stdcall *getNameOfLib)();

typedef IAttack *(__stdcall *getAttackSymbol)(ECS::Manager &ecs, EventManager::Manager &event, LibLoader &libloader);
typedef IMap *(__stdcall *getMapSymbol)();
typedef IMob *(__stdcall *getMobSymbol)(ECS::Manager &ecs, EventManager::Manager &event, LibLoader &libloader, ECS::Components::Position);
typedef IMove *(__stdcall *getMoveSymbol)(ECS::Manager &ecs, EventManager::Manager &event, LibLoader &, ECS::Entity);
typedef IPart *(__stdcall *getPartSymbol)();
typedef IPowerUp *(__stdcall *getPowerUpSymbol)();
typedef IRessources *(__stdcall *getRessourceSymbol)();
typedef IScene *(__stdcall *getSceneSymbol)();
typedef IShipBluprint *(__stdcall *getShipBlueprintSymbol)();

#else

typedef std::string (*getNameOfLib)();

typedef IAttack *(*getAttackSymbol)(ECS::Manager &, EventManager::Manager &, LibLoader &, ECS::Entity);
typedef IMap *(*getMapSymbol)();
typedef IMob *(*getMobSymbol)(ECS::Manager &, EventManager::Manager &, LibLoader &, ECS::Components::Position);
typedef IMove *(*getMoveSymbol)(ECS::Manager &, EventManager::Manager &, LibLoader &, ECS::Entity);
typedef IPart *(*getPartSymbol)();
typedef IPowerUp *(*getPowerUpSymbol)();
typedef IRessources *(*getRessourceSymbol)();
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

template <typename T>
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
      return ((getNameOfLib) (GetProcAddress(hGetProcIDDLL, "getName")))();
#else
      void *handle = dlopen(path.c_str(), RTLD_LAZY);
      return ((getNameOfLib)(dlsym(handle, "getName")))();
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
      return (T) GetProcAddress(hGetProcIDDLL, "getSymbol");
#else
      void *handle = dlopen(path.c_str(), RTLD_LAZY);
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
              std::string nameOfLib = getLibName(curPath);
              T curSymbol = getSymbol(curPath);

              LOG_INFO << "Loading library: " << nameOfLib << std::endl;

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
};

class LibLoader
{
  public:
    __lib__implem<getAttackSymbol> attack;
    __lib__implem<getMapSymbol> map;
    __lib__implem<getMobSymbol> mob;
    __lib__implem<getMoveSymbol> move;
    __lib__implem<getPartSymbol> part;
    __lib__implem<getPowerUpSymbol> powerup;
    __lib__implem<getRessourceSymbol> ressource;
    __lib__implem<getSceneSymbol> scene;
    __lib__implem<getShipBlueprintSymbol> ship_blueprint;

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
};