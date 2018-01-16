#pragma once

#include <AlfredBase/Utils/Singleton.hpp>
#include <string>
#include <future>
#include <config.hpp>
#include <fstream>

#define LOG_DEBUG Logger::get().debug(__FUNCTION__##" ")
#define LOG_INFO Logger::get().info(__FUNCTION__##" ")
#define LOG_WARNING Logger::get().warning(__FUNCTION__" ")
#define LOG_ERROR Logger::get().error(__FUNCTION__" ")
#define LOG_FATAL Logger::get().fatal(__FUNCTION__" ")

enum __CONSOLE_LOG_ENUM
{
  CONSOLE_LOG = 0,
};

static constexpr char DEFAULT_LOG_FILENAME[] = ".log_default.log";

class NullBuffer : public std::streambuf
{
public:
  int overflow(int c)
  { return c; }
};

class Logger : public Alfred::Utils::Singleton<Logger>
{
private:
  NullBuffer null_buffer;
  std::string _fileName;
  std::ostream *_stream;
  std::ostream _nullStream;
  std::ostream *_coutStream;

  std::mutex _mutex;

private:

public:
  Logger() : _stream((new std::ofstream(DEFAULT_LOG_FILENAME, std::ios::trunc))), _nullStream(&null_buffer), _coutStream(&std::cout)
  {
    _fileName = DEFAULT_LOG_FILENAME;
  }

  explicit Logger(const std::string &fileName) : _stream((new std::ofstream(fileName.c_str(), std::ios::trunc))),
                                                 _nullStream(&null_buffer), _coutStream(&std::cout)
  {
    _fileName = fileName;
  }

  explicit Logger(const __CONSOLE_LOG_ENUM console) : _stream(&std::cout), _nullStream(&null_buffer), _coutStream(&std::cout)
  {
    _fileName = "console output";
  }

  virtual ~Logger()
  {
  }

  void setOutput(const __CONSOLE_LOG_ENUM console)
  {
    _fileName = "console output";
    _stream = _coutStream;
  }

  void setOutput(const std::string &filename)
  {
    _fileName = filename;
    _stream = new std::ofstream(filename.c_str(), std::ios::trunc);
  }

  void setOutput()
  {
    _fileName = DEFAULT_LOG_FILENAME;
    _stream = new std::ofstream(DEFAULT_LOG_FILENAME, std::ios::trunc);
  }

  std::ostream &debug(const std::string &funcName = "")
  {
    if constexpr(DEBUG) {
      *_stream << "[DEBUG] " << funcName;
      return *_stream;
    } else {
      return _nullStream;
    }
  }

  std::ostream &info(const std::string &funcName = "")
  {
    *_stream << "[INFO] " << funcName;
    return *_stream;
  }

  std::ostream &warning(const std::string &funcName = "")
  {
    *_stream << "[WARNING] " << funcName;
    return *_stream;
  }

  std::ostream &error(const std::string &funcName = "")
  {
    *_stream << "[ERROR] " << funcName;
    return *_stream;
  }

  std::ostream &fatal(const std::string &funcName = "")
  {
    *_stream << "[FATAL] " << funcName;
    return *_stream;
  }
};