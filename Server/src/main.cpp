/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2017-12-17T18:57:51+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2017-12-21T20:49:46+01:00
 */


#include	"Server.hpp"
#include  "config.hpp"

#include  <iostream>

int     main(int ac, char *av[])
{
  (void)ac;
  (void)av;
  Server	server;

try {
  server.waitClientPacket();
} catch (std::runtime_error &e){
  std::cout << e.what() << std::endl;
}

  if (DEBUG)
    std::cout << "### DEBUG ON ###" << std::endl;

  return (0);
}
