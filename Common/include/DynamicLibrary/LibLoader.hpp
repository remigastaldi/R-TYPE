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

class IAttack;

class IMap;

class IMob;

class IMove;

class IPart;

class IPowerUp;

class IRessources;

class IScene;

class IShipBluprint;

#ifdef WIN32

typedef IAttack *(__stdcall *getAttackSymbol)();
typedef IMap *(__stdcall *getMapSymbol)();
typedef IMob *(__stdcall *getMobSymbol)();
typedef IMove *(__stdcall *getMoveSymbol)();
typedef IPart *(__stdcall *getPartSymbol)();
typedef IPowerUp *(__stdcall *getPowerUpSymbol)();
typedef IRessources *(__stdcall *getRessourceSymbol)();
typedef IScene *(__stdcall *getSceneSymbol)();
typedef IShipBluprint *(__stdcall *getShipBlueprintSymbol)();

#else

typedef IAttack *(*getAttackSymbol)();
typedef IMap *(*getMapSymbol)();
typedef IMob *(*getMobSymbol)();
typedef IMove *(*getMoveSymbol)();
typedef IPart *(*getPartSymbol)();
typedef IPowerUp *(*getPowerUpSymbol)();
typedef IRessources *(*getRessourceSymbol)();
typedef IScene *(*getSceneSymbol)();
typedef IShipBluprint *(*getShipBlueprintSymbol)();

#endif

template <typename T>
class __lib__implem : public Alfred::Utils::NonCopyable
{
  private:
    std::string _osLibEnding;
    //map of file path, file names / bool (is visible), handler
    std::unordered_map<std::string, std::pair<bool, std::vector<std::pair<std::string, T>>>> _files;

  private:
    T getSymbol(std::string path)
    {
#ifdef WIN32
        HINSTANCE hGetProcIDDLL = LoadLibrary(std::move(path));
        if (!hGetProcIDDLL) {
            LOG_ERROR << "could not load the dynamic library" << std::endl;
            return nullptr;
        }
        return (T) GetProcAddress(hGetProcIDDLL, "getSymbol");
#else
        void *handle = dlopen(std::move(path).c_str(), RTLD_LAZY);
        return (T) dlsym(handle, "getSymbol");
#endif
    }

  public:
    __lib__implem()
    {
        if constexpr (the_os == OS::Linux)
            _osLibEnding = ".so";
        else if constexpr (the_os == OS::Mac)
            _osLibEnding = ".dylib";
        else
            _osLibEnding = ".dll";
    }

    std::vector<std::pair<std::string, T>> update()
    {
        std::vector<std::pair<std::string, T>> out;
        for (auto &it : _files) {
            if (it.second.first) {
                for (auto &p: std::experimental::filesystem::directory_iterator(it.first)) {
                    std::string curPath = p.path().generic_string();
                    if (curPath.find(_osLibEnding) != 0) {
                        for (const auto &iterator: it.second.second) {
                            if (iterator.first.find(curPath) != 0) {
                                T curSymbol = getSymbol(curPath);
                                it.second.second.pushback(std::make_pair(curPath, curSymbol));
                                out.push_back(std::make_pair(curPath, curSymbol));
                            }
                        }
                    }
                }
            }
        }
        return out;
    };

    bool addFolder(const std::string &path, const bool toRefresh = false)
    {
        std::experimental::filesystem::directory_entry entry(path);
        if (std::experimental::filesystem::exists(entry))
        {
            _files[path] = std::make_pair(toRefresh, std::vector<std::pair<std::string, T>>());
            return true;
        }
        return false;
    }
};

class LibLoader : public Alfred::Utils::NonCopyable
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
    __lib__implem<getShipBlueprintSymbol> shib_blueprint;

  public:
    explicit LibLoader() = default;
    ~LibLoader() = default;
};