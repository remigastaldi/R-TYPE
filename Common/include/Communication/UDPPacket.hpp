/*
** Packet.hpp for R-TYPE
**
** Made by	Tanguy Lelievre
** Login	leliev_t
**
** Started on	Sat Jan 20 15:45:53 2018 Tanguy Lelievre
** Last update	Sun Jan 21 20:45:39 2018 Tanguy Lelievre
*/

#pragma	once

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
  void	setData(std::string &, std::string &);

  void	deleteData(std::string &);

  std::string	const &getToken();
  void	setToken(std::string &);

  RFC::Commands getCommand() const;
  void	setCommand(std::string &);

  RFC::Commands getResult() const;

  int	getTimestamp() const;
  void	setTimestamp(int);

private:
  std::unordered_map<std::string, std::string>	_data;
};
