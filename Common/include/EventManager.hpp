/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-19T18:07:55+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-19T18:40:12+01:00
 */
#pragma once

#include <string>
#include <functional>
#include <vector>
#include <unordered_map>
#include "AlfredBase/EventManager/EventManagerExceptions.hpp"

#pragma GCC diagnostic ignored "-Wsubobject-linkage"

namespace EventManager
{
  using EventListener = int;

  class ___event_helper
  {
  };

  template <typename Ret, typename ...Params>
  class ___Event : public ___event_helper
  {
      EventListener _loc = 0;
      std::unordered_map<EventListener, std::function<Ret(Params...)>> _watchers;

    public:
      ___Event() :
        _watchers()
      {}

    public:
      EventListener addWatchers(const std::function<Ret(Params...)> &_func)
      {
        _watchers[_loc] = _func;
        _loc += 1;
        return _loc - 1;
      }

      typename std::conditional<std::is_same<Ret, void>::value, void, std::vector<Ret>>::type
      execute(Params ... args)
      {
        if constexpr (!std::is_same<void, Ret>::value) {
          std::vector<Ret> ret;
          for (const auto &it: _watchers) {
            ret.push_back(it.second(args...));
          }
          return ret;
        } else {
          for (const auto &it: _watchers) {
            it.second(args...);
          }
        }
      }

      void deleteWatcher(const EventListener i)
      {
        _watchers.erase(i);
      }
  };

  class Manager
  {
      std::unordered_map<std::string, ___event_helper *> _events;

    public:
      Manager() :
        _events()
      {}

      template <typename Ret, typename ...Params>
      void addEvent(const std::string &name)
      {
        if (_events.count(name) > 0) {
          throw EventNameExist(name);
        }
        _events[name] = new ___Event<Ret, Params...>();
      }

      void deleteEvent(const std::string &name)
      {
        _events.erase(name);
      }

      void clear()
      {
        _events.clear();
      }

      template <typename Ret, typename ...Args>
      typename std::conditional<std::is_same<Ret, void>::value, void, std::vector<Ret>>::type
      fire(const std::string &name, const Args... args)
      {
        if (_events.count(name) <= 0) {
          throw EventDontExist(name);
        }

        if constexpr (std::is_same<Ret, void>::value) {
          static_cast<___Event<Ret, Args...> *>(_events[name])->execute(args...);
          return;
        } else {
          std::vector<Ret> ret = static_cast<___Event<Ret, Args...> *>(_events[name])->execute(args...);
          return ret;
        }
      }

      template <typename Ret, typename ...Params, typename Fctor>
      EventListener listen(const std::string &name, const Fctor &func)
      {
        if (_events.count(name) <= 0) {
          throw EventDontExist(name);
        }
        EventListener ret = static_cast<___Event<Ret, Params...> *>(_events[name])->addWatchers(func);
        return ret;
      }

      template <typename Ret, typename ...Args>
      void unlisten(const std::string &name, const EventListener listenerID)
      {
        static_cast<___Event<Ret, Args...> *>(_events[name])->deleteWatcher(listenerID);
      };
  };
}