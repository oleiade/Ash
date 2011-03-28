#include	<unistd.h>
#include	<stdlib.h>
#include	<dirent.h>

#include	"my.h"
#include	"42sh.h"

int		nb_path(char *str)
{
  int		size;
  int		i;

  size = 0;
  i = 0;
  while (str[i] != '\0')
    {
      if (str[i] != '\0')
	{
	  size++;
	  while (str[i] != '\0' && str[i] != ':')
	    i++;
	  if (str[i] == ':')
	    i++;
	}
    }
  return (size + 1);
}

int		path_size(char *str)
{
  int		size;
  int		i;

  size = 0;
  i = 0;
  while (str[i] != ':' && str[i] != '\0')
    {
      i++;
      size++;
    }
  return (size + 1);
}

int		free_path(char **path)
{
  int		i;

  i = 0;
  while (path[i] != 0)
    {
      free(path[i]);
      i++;
    }
  free(path);
  return (0);
}

char		**path_to_tab(char *str)
{
  char		**new;
  int		i;
  int		j;
  int		k;

  i = 0;
  j = 0;
  new = xmalloc(sizeof(char *) * nb_path(str));
  while (str[i] != '\0')
    {
      k = 0;
      new[j] = xmalloc(sizeof(char) * path_size(str + i));
      while (str[i] != '\0' && str[i] != ':')
	new[j][k++] = str[i++];
      new[j][k] = '\0';
      if (str[i] == ':')
	i++;
      j++;
    }
  new[j] = 0;
  return (new);
}
