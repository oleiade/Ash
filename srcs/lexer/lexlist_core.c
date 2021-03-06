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
** Function that inits the lexical list
** And sets it's vars to their inital
** values.
*/
t_lexlist	*init_lexlist()
{
  t_lexlist	*lexlist;

  lexlist = xmalloc(sizeof(*lexlist));
  lexlist->head = NULL;
  lexlist->tail = NULL;
  lexlist->keys = 0;
  return (lexlist);
}

/*
** Function that fills the given
** Lexical element (t_lexelem)
** with the requested values
** in order to be inserted
** into a lexlist.
*/
t_lexelem	*fill_lexelem(char *elem, t_lextype type)
{
  t_lexelem	*lexelem;

  lexelem = xmalloc(sizeof(*lexelem));
  lexelem->elem = strdup(elem);
  lexelem->type = type;
  free(elem);
  return (lexelem);
}

/*
** Functions that frees all
** the contained elem of a lexlist.
*/

void		free_lexlist(t_lexlist *list, int flag)
{
  t_lexelem	*next;
  t_lexelem	*cur;

  cur = list->head;
  while (cur != NULL)
    {
      next = cur->next;
      if (flag)
	free(cur->elem);
      free(cur);
      cur = next;
    }
  free(list);
}
