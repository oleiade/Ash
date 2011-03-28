#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include	<unistd.h>
#include	<dirent.h>

#include	"my.h"
#include	"42sh.h"

int		built_in_env(char **argv, t_sllist **myenv)
{
  if (argv[1] == 0)
    put_env(*myenv);
  else if (argv[1] != 0)
    fprintf(stderr, "env : no options available\n");
  return (0);
}

int		put_env(t_sllist *myenv)
{
  while (myenv != NULL)
    {
      xwrite(1, myenv->name, strlen(myenv->name));
      xwrite(1, "=", 1);
      xwrite(1, myenv->data, strlen(myenv->data));
      xwrite(1, "\n", 1);
      myenv = myenv->next;
    }
  return (0);
}
