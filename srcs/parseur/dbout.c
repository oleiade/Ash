#include	<stdlib.h>
#include	<stdio.h>
#include	<dirent.h>
#include	<string.h>
#include	<unistd.h>

#include	"42sh.h"
#include	"get_next_line.h"

/*
** Write in a pipe in order to redirect it.
*/

void		writeinpipe(char *keyword, int fd)
{
  char		*tmp;

  tmp = keyword;
  while (tmp)
    {
      xwrite(1, PROMPT2, strlen(PROMPT2));
      tmp = get_next_line(0);
      if (tmp)
	{
	  if (strcmp(tmp, keyword))
	    {
	      xwrite(fd, tmp, strlen(tmp));
	      free(tmp);
	      xwrite(fd, "\n", 1);
	    }
	  else
	    {
	      xclose(fd);
	      tmp = 0;
	    }
	}
      else
	tmp = keyword;
    }
}
