/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-16T14:55:33+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-18T14:59:07+01:00
 */


#pragma once

#include <AlfredBase/Utils/Singleton.hpp>
#include <string>
#include <future>
#include <fstream>
#include <iomanip>
#include <config.hpp>
#include <sstream>
#include <iostream>

#define LOG_DEBUG Logger::get().debug(__FUNCTION__)
#define LOG_INFO Logger::get().info(__FUNCTION__)
#define LOG_WARNING Logger::get().warning(__FUNCTION__)
#define LOG_ERROR Logger::get().error(__FUNCTION__)
#define LOG_FATAL Logger::get().fatal(__FUNCTION__)

enum __CONSOLE_LOG_ENUM
{
    CONSOLE_LOG = 0,
};

static constexpr char DEFAULT_LOG_FILENAME[] = "log_default.log";
static constexpr char DEFAULT_LOG_TIME_FORMAT[] = "%Hh%M:%S";

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
    std::string _dateFormat = DEFAULT_LOG_TIME_FORMAT;

    std::mutex _mutex;

  private:

    const std::string getTime()
    {
        auto in_time_t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

        std::stringstream ss;

        ss << std::put_time(std::localtime(&in_time_t), DEFAULT_LOG_TIME_FORMAT);

        return ss.str();
    }

  public:
    Logger() :
        _stream((new std::ofstream(DEFAULT_LOG_FILENAME, std::ios::trunc))), _nullStream(&null_buffer),
        _coutStream(&std::cout)
    {
        _fileName = DEFAULT_LOG_FILENAME;
    }

    explicit Logger(const std::string &fileName) :
        _stream((new std::ofstream(fileName.c_str(), std::ios::trunc))),
        _nullStream(&null_buffer), _coutStream(&std::cout)
    {
        _fileName = fileName;
    }

    explicit Logger(const __CONSOLE_LOG_ENUM console) :
        _stream(&std::cout), _nullStream(&null_buffer), _coutStream(&std::cout)
    {
        _fileName = "console output";
    }

    virtual ~Logger()
    {
    }

    void setTimeFormat(const std::string &format)
    {
        _dateFormat = format;
    }

    void setOutput(const __CONSOLE_LOG_ENUM console)
    {
        (void) console;
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
            *_stream << "[DEBUG] " << getTime() << " -" << funcName << "- ";
            return *_stream;
        } else {
            return _nullStream;
        }
    }

    std::ostream &info(const std::string &funcName = "")
    {
        *_stream << "[INFO] " << getTime() << " -" << funcName << "- ";
        return *_stream;
    }

    std::ostream &warning(const std::string &funcName = "")
    {
        *_stream << "[WARNING] " << getTime() << " -" << funcName << "- ";
        return *_stream;
    }

    std::ostream &error(const std::string &funcName = "")
    {
        *_stream << "[ERROR] " << getTime() << " -" << funcName << "- ";
        return *_stream;
    }

    std::ostream &fatal(const std::string &funcName = "")
    {
        *_stream << "[FATAL] " << getTime() << " -" << funcName << "- ";
        return *_stream;
    }
};