#include	<stdio.h>
#include	<unistd.h>
#include	<stdlib.h>
#include	<string.h>
#include	<dirent.h>

#include	"my.h"
#include	"42sh.h"

char		*my_getenv(char *var, t_sllist *myenv)
{
  while (myenv != NULL)
    {
      if (strcmp(myenv->name, var) == 0)
	return (myenv->data);
      myenv = myenv->next;
    }
  return ("");
}

char		*mk_envname(char *str)
{
  int		i;
  char		*tp_name;

  i = 0;
  tp_name = xmalloc(sizeof(*tp_name) * (strlen(str) + 1));
  while (str[i] != '=' && str[i] != '\0')
    {
      tp_name[i] = str[i];
      i++;
    }
  tp_name[i] = '\0';
  return (tp_name);
}

char		*mk_envdata(char *str)
{
  int		i;
  int		j;
  char		*tp_data;

  j = 0;
  i = 0;
  tp_data = xmalloc(sizeof(*tp_data) * (strlen(str) + 1));
  while (str[i] != '=')
    i++;
  i++;
  while (str[i] != '\0')
    tp_data[j++] = str[i++];
  tp_data[j] = '\0';
  return (tp_data);
}

int		build_env(char **env, t_sllist **new_env)
{
  int		i;
  char		*tp_data;
  char		*tp_name;

  *new_env = NULL;
  i = 0;
  my_setenv("PATH", "/bin:/usr/bin", new_env);
  while (env[i] != NULL)
    {
      tp_name = mk_envname(env[i]);
      tp_data = mk_envdata(env[i]);
      my_setenv(tp_name, tp_data, new_env);
      free(tp_name);
      free(tp_data);
      i++;
    }
  my_setenv("OLDPWD", "", new_env);
  my_setenv("SHELL", "42sh", new_env);
  return (0);
}

int		free_env(t_sllist *myenv)
{
  t_sllist	*tmp;

  while (myenv != NULL)
    {
      tmp = myenv->next;
      free(myenv->name);
      free(myenv->data);
      free(myenv);
      myenv = tmp;
    }
  return (0);
}
