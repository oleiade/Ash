#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include	<unistd.h>
#include	<dirent.h>

#include	"my.h"
#include	"42sh.h"
#include	"alias.h"

t_alias		*get_alias(char *name, t_alias *alias)
{
  t_alias	*dump;

  dump = alias;
  while (dump != NULL)
    {
      if (strncmp(name, dump->name, strlen(dump->name)) == 0)
	return (dump);
      dump = dump->next;
    }
  return (NULL);
}

/*
** This function remove an alias from the list
*/
int		built_in_unalias(char **argv, t_sllist **my_env)
{
  t_alias	*alias;
  t_alias	*rm_alias;
  int		i;

  my_env = my_env;
  alias = update_alias(0, NULL);
  if (argv[0] && !argv[1])
    fprintf(stderr, UNALIAS_ERR);
  else if (argv[0] && argv[1])
    {
      i = 1;
      while (argv[i])
	{
	  if ((rm_alias = get_alias(argv[i], alias)) != NULL)
	    del_alias(&alias, rm_alias);
	  else
	    fprintf(stderr, "%s%s\n", UNALIAS_UNFOUND, argv[i]);
	  i++;
	}
    }
  else
    fprintf(stderr, "Fucking error with alias comand\n");
  return (0);
}
