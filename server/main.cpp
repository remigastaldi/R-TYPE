/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2017-12-17T18:57:51+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2017-12-18T00:23:32+01:00
 */


#include  "config.hpp"

#include  <iostream>

int     main(int ac, char *av[])
{
  (void)ac;
  (void)av;

  if (BUILD_SERVER)
    std::cout << "BUILD SERVER" << std::endl;
  else
    std::cout << "BUILD GAME WITH SERVER FOR LOCAL" << std::endl;
  return (0);
}
