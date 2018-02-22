/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-02-21T08:40:21+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-21T08:44:11+01:00
 */


/*
** Packet.hpp for R-TYPE
**
** Made by	Tanguy Lelievre
** Login	leliev_t
**
** Started on	Sat Jan 20 15:45:53 2018 Tanguy Lelievre
** Last update	Wed Feb 21 09:09:56 2018 Tanguy Lelievre
*/

#pragma	once

#include <boost/archive/text_oarchive.hpp>
#include <string>
#include <unordered_map>
#include "RFC.hpp"

class	UDPPacket
{
public:
  UDPPacket();
  virtual ~UDPPacket();

  std::string	const &getIp() const;
  void	setIp(std::string &);

  std::unordered_map<std::string, std::string>	const &getData() const;
  void	setData(std::unordered_map<std::string, std::string> &);

  std::string	getData(const std::string &) const;
  void	setData(std::string const &, std::string const &);

  void	deleteData(std::string &);

  std::string	const &getToken();
  void	setToken(const std::string &);

  RFC::Commands getCommand() const;
  void	setCommand(RFC::Commands);

  RFC::Responses getResult() const;
  void	setResult(RFC::Responses);

  unsigned int	getTimestamp() const;
  void	setTimestamp(const std::string &);

private:
  std::unordered_map<std::string, std::string>	_data;

    // friend class boost::serialization::access;
    //
    // template <typename Archive>
    // void serialize(Archive &ar, const unsigned int version) { ar & _data; }

};
