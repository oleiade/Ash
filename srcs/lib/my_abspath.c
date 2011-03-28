/*
** my_abspath.c for my_abspath in /u/all/crevon_t/svn/42sh/trunk
** 
** Made by theo crevon
** Login   <crevon_t@epitech.net>
** 
** Started on  Thu May  6 16:22:53 2010 theo crevon
** Last update Thu May  6 16:22:54 2010 theo crevon
*/

#include	<stdlib.h>
#include	<dirent.h>
#include	<unistd.h>
#include	<string.h>

#include	"42sh.h"
#include	"my.h"
#include	"error_msgs.h"

/*
** Function that converts a relative path
** to an absolute path.
*/
char		*my_abspath(t_sllist **env, char *path)
{
  int		alloc_size;
  char		*home_path;
  char		*abs_path;

  abs_path = NULL;
  home_path = my_getenv("HOME", *env);
  if (path[0] == '~')
    {
      alloc_size = (strlen(path) + strlen(home_path));
      abs_path = xmalloc(alloc_size * sizeof(*abs_path));
      strcat(abs_path, home_path);
      strcat(abs_path, &path[1]);
      return (abs_path);
    }
 else
   return (path);
}
