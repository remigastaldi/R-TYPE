#pragma once

#include <sstream>
#include <map>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <unordered_map>
#include <ostream>

class ConfigurationManager
{
  private:
    std::string _fileName;
    std::unordered_map<std::string, std::string> _config;

  public:
    explicit ConfigurationManager(std::string fileName) :
      _fileName(std::move(fileName)),
      _config()
    {
      readJSON();
      LOG_INFO << "Configuration Loaded:\n" << print() << std::endl;
    }

    std::string print()
    {
      std::string out;

      for (const auto &it : _config)
        out += "Key: " + it.first + " -> " + it.second + "\n";

      return out;
    }

    friend std::ostream &operator<<(std::ostream &os, const ConfigurationManager &manager)
    {
      for (const auto &it : manager._config)
        os << "Key: " << it.first << " -> " << it.second << std::endl;
      return os;
    }

    const std::string getKey(std::string val)
    {
      if (_config.count(val) <= 0)
        return "Not found";
      return _config[val];
    }

    void readJSON()
    {
      std::ifstream file(_fileName);
      if (!file) {
        LOG_ERROR << "Cant't load configuration JSON file" << std::endl;
        return;
      }
      boost::property_tree::ptree root;
      boost::property_tree::read_json(file, root);

      for (const auto &node : root)
      {
        _config[node.first] = node.second.data();
      }
    }
};

