#include	<stdio.h>
#include	<string.h>
#include	<dirent.h>
#include	<unistd.h>
#include	"my.h"
#include	"42sh.h"

int		built_in_echo(char **argv, t_sllist **myenv)
{
  int		i;
  int		n;

  (void)myenv;
  i = 1;
  n = 1;
  if (argv[1])
    {
      if (strcmp(argv[i], "-n") == 0)
	{
	  i++;
	  n = 0;
	}
      while (argv[i])
	{
	  my_putstr(argv[i]);
	  if (argv[i + 1])
	    xwrite(1, " ", 1);
	  i++;
	}
    }
  if (n)
    xwrite(1, "\n", 1);
  return (0);
}
