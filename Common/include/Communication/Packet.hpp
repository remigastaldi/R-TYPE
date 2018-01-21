/*
** Packet.hpp for R-TYPE
**
** Made by	Tanguy Lelievre
** Login	leliev_t
**
** Started on	Sat Jan 20 15:45:53 2018 Tanguy Lelievre
** Last update	Sun Jan 21 01:45:34 2018 Tanguy Lelievre
*/

#pragma	once

#include <string>
#include <unordered_map>

class	Packet
{
public:
  Packet();
  Packet(std::string &, const std::string &);
  ~Packet();

  std::string	const &getIp() const;
  void	setIp(std::string &);

  std::unordered_map<std::string, std::string>	const &getData() const;
  void	setData(std::unordered_map<std::string, std::string> &);

  std::string	getData(const std::string &) const;
  void	setData(std::string &, std::string &);

  std::string	const &getToken();
  void	setToken(std::string &);

  std::string	const &getCommand() const;
  void	setCommand(std::string &);

  int	getTimestamp() const;
  void	setTimestamp(int);

  std::string	toString();

private:
  std::unordered_map<std::string, std::string>	_data;
};
