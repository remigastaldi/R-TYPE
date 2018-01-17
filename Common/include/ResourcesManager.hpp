/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-16T23:09:53+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-17T03:25:00+01:00
 */


#pragma once

#include  <unordered_map>
#include  <memory>
#include <any>
#include <iostream>
class Resourcebase
{
public:
  explicit Resourcebase(const std::string &name)
    : _name(name)
  {}

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

  T &getContent(void)
  {
    return (_resource);
  }

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
	void load(const std::string &name)
	{
    _resources.emplace(name, std::make_shared<C>(C(name)));
	}

  template<typename C>
	std::shared_ptr<C> get(const std::string &name)
	{
    return (std::static_pointer_cast<C>(_resources[name]));
	}

  template<typename S>
	typename S::ContentType &getContent(const std::string &name)
	{
    return (std::static_pointer_cast<S>(_resources[name])->getContent());
	}

  bool release(const std::string &name)
  {
    size_t nb = _resources.erase(name);
    return (nb > 0 ? true : false);
  }

private:
  std::unordered_map<std::string, std::shared_ptr<Resourcebase>> _resources;
};
