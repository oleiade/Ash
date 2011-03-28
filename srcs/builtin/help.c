#include	<stdlib.h>
#include	<stdio.h>
#include	<dirent.h>
#include	<unistd.h>

#include	"my.h"
#include	"42sh.h"

int		built_in_help(char **argv, t_sllist **myenv)
{
  myenv = myenv;
  if (argv[1] == 0)
    my_putstr(HELP);
  else
    fprintf(stderr, ERR_HELP);
  return (0);
}
