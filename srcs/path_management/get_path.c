#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include       	<unistd.h>
#include	<sys/types.h>
#include	<dirent.h>
#include	<fcntl.h>

#include	"my.h"
#include	"42sh.h"
#include	"path.h"
#include	"error_msgs.h"

/*
** Function that puts the global environ
** variable into a double linked list.
** in order to use it on multiple
** environnement operations.
** beware, PATH will always be the first
** link in the list!
*/
t_sllist		**put_path_in_list(t_sllist **env)
{
  char			*path_content;
  t_sllist		**path_dirs;

  path_content = NULL;
  path_content = my_getenv("PATH", *env);
  path_dirs = pathdirs_to_list(path_content);
  return (path_dirs);
}

/*
** Function that formats the requested
** filename, in order to get the possibility
** to "access" it.
*/
char			*format_exec_name(char *foldername, char *filename)
{
  char			*out_string;
  int			exec_path_size;

  exec_path_size = strlen(foldername) + strlen(filename);
  out_string = xmalloc(exec_path_size * sizeof(out_string));
  strcat(out_string, foldername);
  strcat(out_string, "/");
  strcat(out_string, filename);
  return (out_string);
}

static void		exc(t_sllist *tmp, t_sllist **path, struct dirent *dp)
{
  char			*exec_path;

  exec_path = format_exec_name(tmp->data, dp->d_name);
  if (access(exec_path, X_OK) == 0)
    {
      add_to_list(path, NULL, dp->d_name);
      memset(exec_path, 0, strlen(exec_path));
    }
}

/*
** Function that puts all the executable
** files from the dirs contained in the
** PATH environnement var into a double
** linked list.
*/
static t_sllist		**get_execs(t_sllist **path_dirs)
{
  t_sllist		*tmp;
  t_sllist		**path_execs;
  DIR			*odir;
  struct dirent		*dp;

  tmp = *path_dirs;
  path_execs = xmalloc(sizeof(**path_execs));
  while (tmp)
    {
      odir = xopendir(tmp->data);
      while ((dp = readdir(odir)))
	{
	  if ((strncmp(dp->d_name, ".", 1)) != 0 &&
	      (strncmp(dp->d_name, "..", 1) != 0))
	    exc(tmp, path_execs, dp);
	}
      tmp = tmp->next;
    }
  return (path_execs);
}

t_sllist		**put_execs_in_list(t_sllist **env)
{
  t_sllist		**path_execs;
  t_sllist		**path_dirs;

  path_dirs = put_path_in_list(env);
  path_execs = get_execs(path_dirs);
  return (path_execs);
}
