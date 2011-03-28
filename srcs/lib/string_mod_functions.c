/*
** string_mod_functions.c for string_mod_functions in /u/all/crevon_t/svn/42sh/trunk
** 
** Made by theo crevon
** Login   <crevon_t@epitech.net>
** 
** Started on  Thu May  6 16:23:10 2010 theo crevon
** Last update Sun May 23 17:02:58 2010 louis demay-drouhard
*/

#include	<stdlib.h>
#include	<stdio.h>
#include	<fcntl.h>
#include	<sys/types.h>
#include	<ctype.h>
#include	<unistd.h>
#include	<dirent.h>
#include	<string.h>

#include	"my.h"
#include	"42sh.h"
#include	"path.h"
#include	"lexer.h"

int		bypass_spaces(char *str, int pos)
{
  int		in_pos;

  in_pos = pos;
  while (str[in_pos])
    {
      while (str[in_pos] == ' ' ||
	     str[in_pos] == '\t')
	in_pos++;
      return (in_pos);
    }
  return (in_pos);
}

static int	*init_coords(int *coords, char *str)
{
  coords = xmalloc((3 + 1) * sizeof(*coords));
  coords[3] = '\0';
  coords[0] = 0;
  coords[1] = strlen(str) - 1;
  coords[2] = 0;
  return (coords);
}

static int	*get_coords(char *str)
{
  int		*coords;

  coords = 0;
  coords = init_coords(coords, str);
  if (str)
    {
      while ((str[coords[0]] == ' ') ||
	     (str[coords[0]] == '\t'))
	{
	  coords[2]++;
	  coords[0]++;
	}
      while ((str[coords[1]] == ' ') ||
	     (str[coords[1]] == '\t'))
	{
	  coords[2]++;
	  coords[1]--;
	}
      return (coords);
    }
  return (NULL);
}

char		*remove_spaces(char *str)
{
  char		*new_str;
  int		*coords;

  new_str = NULL;
  coords = get_coords(str);
  if (coords)
    {
      new_str = xmalloc(((strlen(str) - coords[2]) + 1) * sizeof(*new_str));
      strncpy(new_str, &str[coords[0]], (size_t)(strlen(str) - coords[2]));
    }
  free(coords);
  free(str);
  return (new_str);
}
