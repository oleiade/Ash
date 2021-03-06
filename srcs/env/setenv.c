#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include	<dirent.h>
#include	<unistd.h>

#include	"my.h"
#include	"42sh.h"

int		is_env_test(char *str)
{
  int		i;

  i = 0;
  while (str[i])
    {
      if (str[i] == '=')
	{
	  fprintf(stderr, "Syntax error\n");
	  return (1);
	}
      i++;
    }
  return (0);
}

int		built_in_setenv(char **argv, t_sllist **myenv)
{
  if (argv[1] == 0)
    {
      put_env(*myenv);
      return (0);
    }
  else if (argv[2] == 0)
    {
      if (is_env_test(argv[1]))
	return (0);
      my_setenv(argv[1], "", myenv);
      return (0);
    }
  else if (argv[3] != '\0')
    {
      if (is_env_test(argv[1]))
        return (0);
      fprintf(stderr, "Usage : setenv [VAR] [VALUE]\n");
      return (1);
    }
  my_setenv(argv[1], argv[2], myenv);
  return (0);
}

int		my_setenv(char *name, char *data, t_sllist **myenv)
{
  t_sllist	*tmp;

  tmp = *myenv;
  while (tmp != NULL)
    {
      if (strcmp(tmp->name, name) == 0)
	{
	  free(tmp->data);
	  tmp->data = xmalloc(sizeof(char *) * (strlen(data) + 1));
	  strcpy(tmp->data, data);
	  return (0);
	}
      tmp = tmp->next;
    }
  add_to_list(myenv, name, data);
  return (0);
}

int		strecmp(char *s1, char *s2)
{
  int		i;

  i = 0;
  while ((s1[i] == s2[i]) && s1[i] != 0 && s2[i++] != 0);
  if (s1[i] == '\0' && s2[i] == '=')
    return (i + 1);
  return (0);
}

char		*my_strnamecpy(char *name, char *env)
{
  int		i;

  i = 0;
  while (env[i] != '\0' && env[i] != '=')
    {
      name[i] = env[i];
      i++;
    }
  name[i] = '\0';
  return (name);
}
