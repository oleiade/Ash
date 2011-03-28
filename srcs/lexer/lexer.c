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
** Main function that gets a lexical list
** from the standard input, in order to be sent
** to the parser.
*/
t_lexlist	*get_lexlist(char *std_in)
{
  char		*new_stdin;
  t_lexlist	*lexlist;
  t_lexelem	*lexelem;
  int		pos;

  if (!std_in)
    return (NULL);
  if (!strlen(std_in))
    {
      free(std_in);
      return (NULL);
    }
  pos = 0;
  lexlist = init_lexlist();
  new_stdin = spacialize_string(std_in);
  if (new_stdin)
    {
      while ((lexelem = get_next_lexelem(new_stdin, &pos, &lexlist)) != NULL)
	insert_in_lexlist(lexlist, lexelem);
      free(new_stdin);
    }
  free(std_in);
  return (lexlist);
}
