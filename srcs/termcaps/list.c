#include	<stdlib.h>
#include	<dirent.h>
#include	<unistd.h>

#include	"42sh.h"
#include	"my.h"
#include	"lexer.h"
#include	"termc.h"

/*
** - Function that empty line
*/
void		empty_line(int len, t_tutils *utils)
{
  begin_line(utils);
  len++;
  while (len)
  {
    my_outc(' ');
    len--;
  }
}

/*
** - Function that make list unselected
** - for put cursor to the string end.
*/
void		unselect_list(t_termc *list)
{
  t_com		*com;

  com = list->begin;
  while (com)
  {
    com->is_on = 0;
    com = com->next;
  }
  list->is_ready = 1;
}

/*
** - Return struct where cursor is on.
*/
t_com		*find_is_on(t_termc *list)
{
  t_com		*buff;

  buff = list->begin;
  while (buff != NULL && !buff->is_on)
    buff = buff->next;
  return (buff);
}

/*
** - Delete struct passed in params from char list
*/
void		del_char(t_termc *list, t_com *com)
{
  if (com)
  {
    if (com->prev)
      com->prev->next = com->next;
    else
      list->begin = com->next;
    if (com->next)
      com->next->prev = com->prev;
    else
      list->end = com->prev;
    list->nb_char--;
    free(com);
  }
}

/*
** - Make string from list
*/
char		*list_to_char(t_termc *list)
{
  int		count;
  char		*res;
  t_com		*buff;

  count = 0;
  if (list)
  {
    buff = list->begin;
    res = xmalloc((list->nb_char + 1) * sizeof(*res));
    while (count < list->nb_char)
    {
      res[count] = buff->c;
      count++;
      buff = buff->next;
    }
    return (res);
  }
  return ("");
}
