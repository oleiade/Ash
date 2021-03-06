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

static int		get_nextelem_size(char *str, int pos)
{
  int		in_pos;
  int		size;

  in_pos = bypass_spaces(str, pos);
  size = 0;
  while (str[in_pos])
    {
      while ((str[in_pos] != ' ') &&
	     (str[in_pos] != '\t') &&
	     (str[in_pos] != '\0'))
	{
	  size++;
	  in_pos++;
	}
      return (size);
    }
  return (0);
}

static char		*get_next_elem(char *str, int *pos)
{
  char		*out_str;

  out_str = xmalloc((get_nextelem_size(str, *pos) + 1) * sizeof(*out_str));
  *pos = bypass_spaces(str, *pos);
  while (str[*pos])
    {
      while ((str[*pos] != ' ') &&
	     (str[*pos] != '\t') &&
	     (str[*pos] != '\0'))
	{
	  strncat(out_str, &str[*pos], 1);
	  (*pos)++;
	}
      return (remove_spaces(out_str));
    }
  return (NULL);
}

static t_lextype	get_elem_type(char *str, int pos)
{
  t_lextype		lextype;

  lextype = 0;
  if (pos >= 1)
    lextype = get_lextype(str[pos - 1], str[pos], str[pos + 1]);
  else if (!pos)
    lextype = get_lextype(0, str[pos], str[pos + 1]);
  return (lextype);
}

static t_lexelem       	*free_empty_quotes(t_lexelem *out_elem,
					   t_lexlist **lexlist)
{
  free(out_elem);
  free_lexlist(*lexlist, 0);
  *lexlist = NULL;
  return (NULL);
}

t_lexelem		*get_next_lexelem(char *str, int *pos,
					  t_lexlist **lexlist)
{
  int		in_pos;
  t_lextype	lextype;
  t_lexelem	*out_elem;

  out_elem = xmalloc(sizeof(*out_elem));
  *pos = bypass_spaces(str, *pos);
  in_pos = *pos;
  while (in_pos < (int)strlen(str))
    {
      lextype = get_elem_type(str, in_pos);
      if ((lextype == DQUOTE || (lextype == QUOTE)))
	{
	  if ((out_elem->elem = manage_quote(str, &in_pos)) == NULL)
	    return (free_empty_quotes(out_elem, lexlist));
	}
      else
	out_elem->elem = get_next_elem(str, &in_pos);
      *pos = in_pos + 1;
      out_elem->type = lextype;
      return (out_elem);
    }
  return (NULL);
}
