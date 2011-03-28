#include	<unistd.h>
#include	<stdlib.h>
#include	<string.h>
#include	<dirent.h>

#include	"my.h"
#include	"42sh.h"

static const t_builtin	gl_builtin[] =
  {
    {"cd", built_in_cd},
    {"env", built_in_env},
    {"unsetenv", built_in_unsetenv},
    {"setenv", built_in_setenv},
    {"echo", built_in_echo},
    {"help", built_in_help},
    {"alias", built_in_alias},
    {"unalias", built_in_unalias},
    {"history", built_in_history},
    {0, 0},
  };

int		execute_builtin(t_fifo_elem *cur, t_sllist **myenv)
{
  int		i;
  int		return_val;
  int		old_out;

  old_out = 0;
  i = 0;
  if (strcmp("exit", cur->data.argv[0]) == 0)
    return (QUIT);
  while (gl_builtin[i].built_in != 0)
    if (strcmp(gl_builtin[i++].built_in, cur->data.argv[0]) == 0)
      {
	if (cur->data.fd[OUT])
	  {
	    old_out = dup(1);
	    xdup2(cur->data.fd[OUT], 1);
	  }
	return_val = gl_builtin[i - 1].ptr_built_in(cur->data.argv, myenv);
	if (cur->data.fd[OUT])
	  xdup2(old_out, 1);
	return (return_val);
      }
  return (EXIT_FAILURE);
}

int		is_builtin(char *c)
{
  int		j;

  j = -1;
  if (!strcmp("exit", c))
    return (1);
  while (gl_builtin[++j].built_in)
    {
      if (!strcmp(gl_builtin[j].built_in, c))
	return (1);
    }
  return (0);
}
