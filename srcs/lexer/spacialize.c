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
** Function that sets the spaces where they're needed
** in/out the stdin quotations.
*/
static char	*spacialize_quotes(char *str, char *new_str, int *pos)
{
  int		buf_pos;

  buf_pos = 0;
  if (*pos > 0)
    if ((str[*pos - 1]) && (str[*pos - 1] != ' '))
      strncat(new_str, " ", 1);
  buf_pos = *pos;
  (*pos)++;
  while (str[*pos] && (str[buf_pos] != str[*pos]))
    (*pos)++;
  strncat(new_str, &str[buf_pos], *pos - buf_pos + 1);
  (*pos)++;
  return (new_str);
}

static void	manage_prec_sp(char *new_str, char *str, int *pos, int *st)
{
  int		len;

  len = strlen(str);
  if ((*pos > 1) && (*pos < len))
    if (!prec_space(str[*pos - 2], str[*pos - 1], str[*pos], str[*pos + 1]))
      {
	strcat(new_str, " ");
	strncat(new_str, &str[*pos], 1);
	*st = 1;
      }
}

static void	manage_next_sp(char *new_str, char *str, int *pos, int *st)
{
  int		len;

  len = strlen(str);
  if (*pos < (len - 1))
    {
      if (!next_space(str[*pos], str[*pos + 1], str[*pos + 2]) &&
	  (str[*pos + 1] != '|' && str[*pos + 1] != '&' &&
	   str[*pos + 1] != ' '))
	{
	  if (*st == 0)
	    strncat(new_str, &str[*pos], 1);
	  strcat(new_str, " ");
	}
      else if (*st == 0)
	strncat(new_str, &str[*pos], 1);
    }
  else if (*st == 0)
    strncat(new_str, &str[*pos], 1);
}

/*
** Function that sets the correct spaces where they're
** needed in the rest of the std_in elements.
*/
static char	*spacialize_misc(char *str, char *new_str, int *pos, int *st)
{
  int		len;

  len = strlen(str);
  manage_prec_sp(new_str, str, pos, st);
  manage_next_sp(new_str, str, pos, st);
  (*pos)++;
  *st = 0;
  return (new_str);
}

char		*spacialize_string(char *str)
{
  char		*new_str;
  int		pos;
  int		st;

  pos = 0;
  st = 0;
  new_str = xmalloc((get_stdin_newsize(str) + 1) * sizeof(*new_str));
  if (strlen(str) > 0)
  {
    if ((IS_QUOTE(str[pos])) || (IS_DQUOTE(str[pos])))
      new_str = spacialize_quotes(str, new_str, &pos);
    else
      new_str = spacialize_misc(str, new_str, &pos, &st);
   }
  while (pos <= (int)strlen(str) && str[pos])
    {
      if (((IS_QUOTE(str[pos])) || (IS_DQUOTE(str[pos]))) &&
	  (str[pos - 1] != '\\'))
	new_str = spacialize_quotes(str, new_str, &pos);
      else
	new_str = spacialize_misc(str, new_str, &pos, &st);
    }
  return (new_str);
}
