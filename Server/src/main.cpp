/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2017-12-17T18:57:51+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2017-12-21T20:49:46+01:00
 */


#include  "config.hpp"

#include  <iostream>

int     main(int ac, char *av[])
{
  (void)ac;
  (void)av;

  if (DEBUG)
    std::cout << "### DEBUG ON ###" << std::endl;

  return (0);
}
