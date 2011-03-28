#include	<unistd.h>
#include	<stdlib.h>
#include	<string.h>
#include	<errno.h>
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<fcntl.h>
#include	<stdio.h>
#include	<dirent.h>

#include	"my.h"
#include	"42sh.h"
#include	"conf.h"
#include	"get_next_line.h"
#include	"alias.h"

/*
** Send the line to the parser/lexer.
*/
char		*concat_filename(char *filename, char *home)
{
  char		*full_fn;

  if (home[0] != 0)
    {
      full_fn = xmalloc(sizeof(char) * (strlen(home) + strlen(filename) + 2));
      strcat(full_fn, home);
      strcat(full_fn, "/");
      strcat(full_fn, filename);
    }
  else
    full_fn = filename;
  return (full_fn);
}

int		check_file(char *filename, char *home)
{
  char		*full_fn;
  int		fd;

  fd = 0;
  full_fn = concat_filename(filename, home);
  if (access(full_fn, R_OK) == 0)
    {
      fd = xopen(full_fn, O_RDONLY, 0644);
      if (home[0] != 0)
	free(full_fn);
      return (fd);
    }
  else
    {
      fd = xopen(full_fn, O_CREAT, 0644);
      if (access(full_fn, R_OK) == 0)
	fprintf(stderr, CONF_ERR);
      if (home[0] != 0)
	free(full_fn);
      return (fd);
    }
  return (-1);
}

void		load_conf(t_sllist **myenv)
{
  int		fd;
  char		*buffer;
  t_lexlist	*list;
  char		*home;

  fd = 0;
  home = my_getenv("HOME", *myenv);
  list = NULL;
  buffer = NULL;
  if ((fd = check_file(CONF_NAME, home)) != -1)
    {
      while ((buffer = get_next_line(fd)) != NULL)
	{
	  if ((buffer[0] != COMMENT_CHAR) && (buffer[0]))
	    {
	      list = get_lexlist(buffer);
	      parser(list, myenv);
	    }
	}
    }
  xclose(fd);
  return ;
}
