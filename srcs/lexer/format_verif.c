#include	<stdlib.h>
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
** Local function that defines a state
** for chars that calls a closing one
** like ' " or `
*/
int		calls_a_close(char c)
{
  if (IS_QUOTE(c) || IS_BQUOTE(c) ||
      IS_DQUOTE(c))
    return (1);
  return (0);
}

/*
** Function that checks if everything that has been open
** such as " ' ` or ( has been closed before lexing
*/
int		verify_format(char *in)
{
  int		p;
  char		oc;

  oc = 0;
  p = 0;
  while (in[p])
    {
      if (oc == 0)
	{
	  if (calls_a_close(in[p]) || IS_OPENPAR(in[p]))
	    oc = in[p];
	  p++;
	}
      else if (oc != 0)
	{
	  if ((oc == in[p]) || ((IS_CLOSEPAR(in[p])) && (in[p - 1] != '\\')))
	    oc = 0;
	  p++;
	}
      else
	p++;
    }
  if (oc != 0)
    return (1);
  return (0);
}
