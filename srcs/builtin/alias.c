#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include	<dirent.h>
#include	<unistd.h>
#include	"my.h"
#include	"42sh.h"
#include	"alias.h"

/*
** This function return a copy of an alias.
** Don't forget to free it !
*/
char	       	*check_if_alias(char *cmd, char *bkcmd, int f)
{
  t_alias		*alias;
  t_alias		*dump;
  static int		i = 0;

  alias = update_alias(0, NULL);
  dump = alias;
  while (dump != NULL)
    {
      if (i == ALIAS_LOCK)
	{
	  fprintf(stderr, ERR_LOOP);
	  i = 0;
	  return (strdup(bkcmd));
	}
      if (strncmp(cmd, dump->name, strlen(cmd)) == 0 &&
	  (strlen(cmd) == strlen(dump->name)))
	if (strcmp(cmd, dump->value) != 0)
	  return (check_if_alias(dump->value, bkcmd, 1));
      dump = dump->next;
      i++;
    }
  i = 0;
  if (f == 1)
    return (strdup(cmd));
  return (NULL);
}

/*
** This function update the alias pointers list
** flag 1 -> Initialise the list
** flag 2 -> update the alias with thenew pointer
*/
t_alias			*update_alias(int flag, t_alias *new_alias)
{
  static t_alias	*alias;

  if (flag == 1)
    alias = NULL;
  else if (flag == 2)
    alias = new_alias;
  return (alias);
}

int			count_equal(char *s)
{
  int			i;
  int			equal;

  equal = 0;
  i = 0;
  while (s[i])
    {
      if (s[i] == '=')
	equal++;
      i++;
    }
  return (equal);
}

/*
** This function call the others functions.
** Print the alias list or add an alias.
*/
int			built_in_alias(char **argv, t_sllist **my_env)
{
  t_alias		*alias;
  int			i;

  my_env = my_env;
  alias = update_alias(0, NULL);
  if (argv[0] && !argv[1])
    list_alias(alias);
  else if (argv[0] && argv[1])
    {
      i = 1;
      while (argv[i])
	{
	  if (count_equal(argv[i]) == 0)
	    print_alias(alias, argv[i]);
	  else
	    i = put_alias(alias, argv[i], argv[i + 1], i);
	  i++;
	}
    }
  else
    fprintf(stderr, ERR_ALIAS);
  return (0);
}
