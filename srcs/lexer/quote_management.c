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

/*
** Function that gets a quotation
** space size.
*/
int			get_quote_size(char *std_in, int pos, char seek_char)
{
  int			in_pos;
  int			size;

  in_pos = pos;
  size = 0;
  while (std_in[in_pos])
    {
      if (in_pos > 0)
	{
	  if ((std_in[in_pos] == seek_char) && std_in[in_pos - 1] != '\\')
	    return (size);
	}
      else
	if ((std_in[in_pos] == seek_char))
	  return (size);
      in_pos++;
      size++;
    }
  return (-1);
}

/*
** Function that sets the full content of a quotation
** as a single string.
*/
char			*manage_quote(char *std_in, int *pos)
{
  char			*out_elem;
  int			in_pos;
  char			seek_char;
  int			new_size;

  seek_char = std_in[*pos];
  (*pos)++;
  new_size = get_quote_size(std_in, *pos, seek_char);
  out_elem = NULL;
  if (new_size >= 0)
    {
      out_elem = xmalloc((new_size + 1) * sizeof(*out_elem));
      in_pos = *pos;
      (*pos) += new_size;
      strncpy(out_elem, &std_in[in_pos], new_size);
    }
  else
    {
      fprintf(stderr, ERR_UNMAQUO);
      return (NULL);
    }
  return (out_elem);
}
