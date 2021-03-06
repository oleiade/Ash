#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include	<dirent.h>
#include	<unistd.h>
#include	"my.h"
#include	"42sh.h"
#include	"alias.h"

void			parse_alias(t_alias *alias,
				    char *the_alias)
{
  int			i;
  int			j;
  char			*alias_name;
  char			*alias_value;

  alias_name = xmalloc(strlen(the_alias) + 1);
  alias_value = xmalloc(strlen(the_alias) + 1);
  i = 0;
  while (the_alias[i] != '\0' && the_alias[i] != '=')
    {
      alias_name[i] = the_alias[i];
      i++;
    }
  alias_name[i] = '\0';
  if (strlen(alias_name) == 0)
    return ;
  i++;
  j = 0;
  while (the_alias[i] != '\0' && the_alias[i] != '=')
    alias_value[j++] = the_alias[i++];
  alias_value[j] = '\0';
  check_alias(alias_name, alias_value, alias);
  free(alias_name);
  free(alias_value);
}

void			parse2_alias(t_alias *alias,
				     char *the_alias,
				     char *the_alias2)
{
  int			i;
  int			j;
  char			*alias_name;
  char			*alias_value;

  alias_name = xmalloc(strlen(the_alias) + 1);
  alias_value = xmalloc(strlen(the_alias2) + 1);
  i = 0;
  while (the_alias[i] != '\0' && the_alias[i] != '=')
    {
      alias_name[i] = the_alias[i];
      i++;
    }
  alias_name[i] = '\0';
  if (strlen(alias_name) == 0)
    return ;
  i = 0;
  j = 0;
  while (the_alias2[i] != '\0' && the_alias2[i] != '=')
    alias_value[j++] = the_alias2[i++];
  alias_value[j] = '\0';
  check_alias(alias_name, alias_value, alias);
  free(alias_name);
  free(alias_value);
}

int			put_alias(t_alias *alias,
				  char *the_alias,
				  char *the_alias2,
				  int i)
{
  int			len;

  len = strlen(the_alias);
  if (the_alias2 != NULL && the_alias[len - 1] == '=')
    {
      parse2_alias(alias, the_alias, the_alias2);
      return (i + 1);
    }
  else
    {
      parse_alias(alias, the_alias);
      return (i);
    }
  return (i);
}
