/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-16T23:09:53+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-16T23:24:50+01:00
 */


#pragma once

#include  <unordered_map>
#include  <memory>

class Resource
{
public:
  explicit Resource(const std::string &name)
    : _name(name)
  {}

protected:
  std::string _name;
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
    _resources.emplace(name, C(name));
	}

  template<typename C>
	std::shared_ptr<C> get(const std::string &name)
	{
    return (_resources[name]);
	}

  bool release(const std::string &name)
  {
    size_t nb = _resources.erase(name);
    return (nb > 0 ? true : false);
  }

private:
  std::unordered_map<std::string, Resource> _resources;
};
