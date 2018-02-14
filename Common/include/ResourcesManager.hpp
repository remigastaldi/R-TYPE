/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-16T23:09:53+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-21T08:06:24+01:00
 */


#pragma once

#include  <unordered_map>
#include  <memory>
#include <Logger/Logger.hpp>

class Resourcebase
{
public:
  explicit Resourcebase(const std::string &name)
    : _name(name)
  {}
  virtual ~Resourcebase(){};

  const std::string &getName(void) const
  {
    return (_name);
  }

protected:
  std::string _name;
};

template<class T>
class Resource : public Resourcebase
{
public:
  explicit Resource(const std::string &name)
    : Resourcebase(name),
    _resource()
  {}

  Resource(const std::string &name, T resource)
    : Resourcebase(name),
    _resource(resource)
  {}

  virtual ~Resource(){};

  T &getContent(void)
  {
    return (_resource);
  }

  virtual void  loadFromFile(const std::string &) {};

  typedef T ContentType;
protected:
  T  _resource;
};

class ResourcesManager
{
public:
  ResourcesManager()
    : _resources()
  {}

	~ResourcesManager()
	{}

  template<typename C>
	std::shared_ptr<C> load(const std::string &name, const std::string &path)
	{
    if (_resources.find(name) != _resources.end())
      LOG_ERROR << "Ressource " << name << " already exist" << std::endl;
    std::shared_ptr<C> resource(std::make_shared<C>(C(name)));
    resource->loadFromFile(path);
    _resources.emplace(name, resource);
    return (resource);
	}

  template<typename C>
	std::shared_ptr<C> get(const std::string &name)
	{
    if (_resources.find(name) == _resources.end())
      LOG_ERROR << "Ressource " << name << " dont exist" << std::endl;

    return (std::static_pointer_cast<C>(_resources[name]));
	}

  template<typename S>
	typename S::ContentType &getContent(const std::string &name)
	{
    if (_resources.find(name) == _resources.end())
      LOG_ERROR << "Ressource " << name << " dont exist" << std::endl;

    return (std::static_pointer_cast<S>(_resources[name])->getContent());
	}

  template<typename C>
	void addResource(const std::string &name, C &resource)
	{
    if (_resources.find(name) != _resources.end())
      LOG_ERROR << "Ressource " << name << " already exist" << std::endl;
      _resources.emplace(name, std::make_shared<C>(C(name, resource)));
	}

  bool release(const std::string &name)
  {
    size_t nb = _resources.erase(name);
    return (nb > 0 ? true : false);
  }

  void releaseAll(void)
  {
    _resources.clear();
  }

private:
  std::unordered_map<std::string, std::shared_ptr<Resourcebase>> _resources;
};
