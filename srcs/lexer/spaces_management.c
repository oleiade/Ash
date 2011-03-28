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

int	prec_space(char p_prec, char prec, char pos, char next)
{
  t_lextype	lextype_first;
  t_lextype	lextype_sec;

  if (((lextype_first = get_lextype(0, pos, next)) != WORD) &&
      ((lextype_sec = get_lextype(0, prec, pos)) != lextype_first) &&
      ((prec != ' ') && (prec != '&')))
    return (0);
  else if (((pos == '&') || (pos == '|') || (pos == '<') || (pos == '>')) &&
	   ((prec == pos) && (p_prec == pos)))
    return (0);
  else if ((pos == '&') && ((prec != pos) && (prec != ' ')))
    return (0);
  else if (((prec == '(') && (pos == '(')) ||
	   ((prec == ')') && (pos == ')')))
    return (0);
  else if (((prec == '`') && (pos == '`')) ||
	   ((prec != ' ') && (pos == '\'')) ||
	   ((prec != ' ') && (pos == '"')))
    return (0);
  return (1);
}

int	next_space(char pos, char next, char n_next)
{
  t_lextype	lextype;

  if (((lextype = get_lextype(0, pos, next)) != WORD) &&
      ((lextype = get_lextype(0, next, n_next)) == WORD) &&
      (next != ' '))
    return (0);
  else if (((pos == '&') || (pos == '|')) && (next != ' '))
    return (0);
  else if (((pos == '(') && (next != ' ')) ||
	   ((next == ')') && (next != ')')))
    return (0);
  return (1);
}
