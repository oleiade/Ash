#include	<stdlib.h>
#include	<fcntl.h>
#include	<sys/types.h>
#include	<ctype.h>
#include	<unistd.h>
#include	<dirent.h>
#include	<string.h>

#include	"my.h"
#include	"42sh.h"
#include	"lexer.h"
#include	"path.h"

/*
** Function that checks if the requested
** chars contains or are a delimiter (| || ; &&)
*/
int		is_delim(char a, char b)
{
  if (((a == '|') && (b != '|')) ||
      (a == ';'))
    return (1);
  else
    {
      if (((a == '|') && (b == '|')) ||
	  ((a == '&') && (b == '&')))
	return (1);
    }
  return (0);
}

/*
** Function that checks if the requested
** chars contains or are redirections (< << >> >)
*/
int		is_redirection(char a, char b)
{
  if (((a == '<') && ((b != '<') && (b != '>'))) ||
      ((a == '>') && ((b != '>') && (b != '<'))))
    return (1);
  else
    if (((a == '<') && (b == '<')) ||
	((a == '>') && (b == '>')))
      return (1);
  return (0);
}

int		is_and(char a, char b)
{
  if ((a == '&') && (b != '&'))
    return (1);
  return (0);
}

/*
** Function that gets the lexical type
** of a requested element (always symbolized
** by two chars in order to fit to || or && etc.
*/
t_lextype	get_lextype(char a, char b, char c)
{
  t_lextype	lextype;

  lextype = WORD;
  if (is_delim(b, c))
    lextype = DELIM;
  else if (is_redirection(b, c))
    lextype = REDIR;
  else if (is_and(b, c))
    lextype = AND;
  else if (IS_PAR(b))
    lextype = PAR;
  else if (IS_QUOTE(b) && a != '\\')
    lextype = QUOTE;
  else if (IS_DQUOTE(b) && a != '\\')
    lextype = DQUOTE;
  else if (IS_BQUOTE(b))
    lextype = BACKQUOTE;
  return (lextype);
}
