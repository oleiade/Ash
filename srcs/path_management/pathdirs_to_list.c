#include	<stdlib.h>
#include	<dirent.h>
#include	<unistd.h>

#include	"my.h"
#include	"42sh.h"
#include	"error_msgs.h"

/*
** Function that counts the directories
** contained in the PATH environnement
** var.
*/
static int	count_dirs(char *path_str)
{
  int		pos;
  int		dirs_count;

  pos = 0;
  dirs_count = 0;
  while (path_str[pos] != '\0')
    {
      if (path_str[pos] != ':')
	pos++;
      else
	{
	  pos++;
	  dirs_count++;
	}
    }
  dirs_count++;
  return (dirs_count);
}

/*
** Function that returns the next PATH
** environnement directory, in order to
** store it in a double linked list.
*/
static char	*return_dir(char *path_str, int *str_pos)
{
  char		*out_dir;
  int		str_pos_cpy;
  int		dir_size;

  out_dir = NULL;
  dir_size = 0;
  str_pos_cpy = *str_pos;
  while (path_str[str_pos_cpy] != ':' && path_str[str_pos_cpy] != '\0')
    {
      dir_size++;
      str_pos_cpy++;
    }
  out_dir = xmalloc(dir_size * sizeof(char *));
  str_pos_cpy = 0;
  while (path_str[*str_pos] != ':' && path_str[*str_pos] != '\0')
    {
      out_dir[str_pos_cpy] = path_str[*str_pos];
      str_pos_cpy++;
      (*str_pos)++;
    }
  (*str_pos)++;
  return (out_dir);
}

/*
** Function that puts all the dirs
** stored in the PATH environnement
** string into a double linked lists.
*/
t_sllist	**pathdirs_to_list(char *path_str)
{
  int		dirs_count;
  int		words_found;
  int		str_pos;
  t_sllist	**path_dirs;

  dirs_count = count_dirs(path_str);
  words_found = 0;
  path_dirs = xmalloc(sizeof(**path_dirs));
  str_pos = 0;
  while (words_found < dirs_count)
    {
      add_to_list(path_dirs, NULL, return_dir(path_str, &str_pos));
      words_found++;
    }
  return (path_dirs);
}
