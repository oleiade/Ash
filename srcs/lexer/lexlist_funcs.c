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
** Function which inserts the first
** lexelem of a lexlist. And defines
** As well the head and tail pointers
** to the newly inserted lexelem.
*/
int		insert_first_elem(t_lexlist *lexlist, t_lexelem *lexelem)
{
  lexelem->next = lexlist->tail;
  lexelem->prev = lexlist->head;
  lexlist->tail = lexelem;
  lexlist->head = lexelem;
  lexlist->keys++;
  return (0);
}

/*
** Function that inserts a new
** lexical element (t_lexelem)
** at the end of the lexical list.
** Std_in can be parsed from end
** to beginning then.
*/
int		insert_in_lexlist(t_lexlist *lexlist, t_lexelem *lexelem)
{
  if (lexlist->tail == NULL)
    return (insert_first_elem(lexlist, lexelem));
  lexelem->next = NULL;
  lexelem->prev = lexlist->tail;
  lexlist->tail->next = lexelem;
  lexlist->tail = lexelem;
  lexlist->keys++;
  return (0);
}

/*
** Function deletes and frees
** the first elem of a lexlist
** in order to free it.
*/
int		del_first_lexelem(t_lexlist *lexlist)
{
  t_lexelem	*tmp;

  tmp = lexlist->head;
  lexlist->head = lexlist->head->next;
  if (lexlist->head == NULL)
    lexlist->tail = NULL;
  else
    lexlist->head->prev = NULL;
  free (tmp);
  lexlist->keys--;
  return (0);
}
