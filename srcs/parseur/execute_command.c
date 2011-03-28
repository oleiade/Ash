#include	<stdlib.h>
#include	<unistd.h>
#include	<stdio.h>
#include	<dirent.h>
#include	<string.h>

#include	"42sh.h"

/*
** - Prepare the path for a binary in the current folder.
*/

static char	*pwd_path(char **argv, t_sllist **myenv, char *path)
{
  char		*new;

  new = xmalloc(sizeof(char) *
		(strlen(path) + strlen(my_getenv("PWD", *myenv)) + 2));
  strcpy(new, my_getenv("PWD", *myenv));
  if (argv[0] + 2)
    {
      strcat(new, "/");
      strcat(new, argv[0] + 2);
    }
  free(path);
  return (new);
}

/*
** - Prepare the path of a binary for execution.
*/

static char    	*check_path(t_sllist **myenv, char *new_path)
{
  char		**path;
  char		*bin;
  int		i;

  i = 0;
  path = path_to_tab(my_getenv("PATH", *myenv));
  while (path[i] != 0)
    {
      bin = xmalloc(sizeof(char) * 512);
      memset(bin, 0, 512);
      strcat(bin, path[i]);
      strcat(bin, "/");
      strcat(bin, new_path);
      if (access(bin, X_OK) == 0)
        {
          free(new_path);
	  free_path(path);
          return (bin);
        }
      free(bin);
      i++;
    }
  free_path(path);
  return (0);
}

/*
** - Execute a binary and prepare the full path for execve.
** - Creates the env**.
*/

int	    	execute_extern(char **argv, t_sllist **myenv)
{
  char		**env;
  char		*path;

  path = strdup(argv[0]);
  env = list_to_tab(*myenv);
  if (strncmp("./", argv[0], 1) == 0)
    path = pwd_path(argv, myenv, path);
  else if (argv[0][0] != '/')
    path = check_path(myenv, path);
  xexecve(argv, env, path);
  exit(EXIT_FAILURE);
}

