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

void		manage_size(char *str, int *pos, int *size, int size_buf)
{
  if (*pos > 1)
    {
      if (*pos + 1 < size_buf)
	{
	  if (!prec_space(str[*pos - 2], str[*pos - 1],
			  str[*pos], str[*pos + 1]))
	    (*size)++;
	  if (*pos + 3 < size_buf)
	    {
	      if (!next_space(str[*pos], str[*pos + 1], str[*pos + 2]))
		(*size)++;
	    }
	  else
	    (*size)++;
	}
      else
	(*size)++;
    }
  else
    (*size)++;
  (*pos)++;
}

/*
** Function that gets the stdin size
** including the needed spaces in order
** to malloc the correct output size.
*/
int     	get_stdin_newsize(char *str)
{
  int		size;
  int		size_buf;
  int		pos;

  size = strlen(str);
  size_buf = size;
  pos = 0;
  while (str[pos])
    manage_size(str, &pos, &size, size_buf);
  return (size);
}
