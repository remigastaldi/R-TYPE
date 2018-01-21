/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-21T19:52:50+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-21T22:00:21+01:00
 */


#pragma once

#include  "EventManager.hpp"
#include  "Resources.hpp"

class SoundManager
{

  class SoundEvent
  {
  public:
    explicit SoundEvent(ResourcesManager &resourcesManager, const std::string &name)
      : _sound(),
      _name(name),
      _resourcesManager(resourcesManager),
      _listenerID()
    {}

    ~SoundEvent(){};

    void setListenerID(EventManager::EventListener listenerID)
    {
      _listenerID = listenerID;
    }

    EventManager::EventListener getListenerID(void)
    {
      return (_listenerID);
    }

    void playSound(void)
    {
      _sound.setBuffer(_resourcesManager.getContent<SoundBuffer>(_name));
      _sound.play();
    }

  private:
    sf::Sound _sound;
    std::string _name;
    ResourcesManager &_resourcesManager;
    EventManager::EventListener _listenerID;
  };


public:
  SoundManager(ResourcesManager &resourceManager, EventManager::Manager &eventManager)
    : _resourcesManager(resourceManager),
    _eventManager(eventManager)
  {}

  template <typename Ret, typename ...Params>
  void registerSoundWithEvent(const std::string &sound, const std::string &event)
  {
    if (_resources.find(sound) != _resources.end())
      LOG_ERROR << "Ressource " << sound << " already exist" << std::endl;

    std::shared_ptr<SoundEvent> ptr = std::make_shared<SoundEvent>(_resourcesManager, sound);
    EventManager::EventListener listenerID = _eventManager.listen<Ret, Params...>(event, [ptr](Params...) { ptr->playSound();});
    ptr->setListenerID(listenerID);
    _resources.emplace(sound, ptr);
  }

  template <typename Ret, typename ...Params>
  void unRegisterSound(const std::string &sound, const std::string &event)
  {
    _resources.erase(sound);
    _eventManager.unlisten<Ret, Params...>(event, _resources[sound]->getListenerID());
  }

  void loadSound(const std::string &name, const std::string &path)
  {
    _resourcesManager.load<SoundBuffer>(name, path);
  }

private:
  ResourcesManager  &_resourcesManager;
  EventManager::Manager &_eventManager;

  std::unordered_map<std::string, std::shared_ptr<SoundEvent>> _resources;
};
