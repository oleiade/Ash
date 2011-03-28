#include	<stdlib.h>
#include	<dirent.h>
#include	<string.h>
#include	<stdio.h>
#include	<unistd.h>

#include	"42sh.h"
#include	"lexer.h"
#include	"alias.h"

/*
** - Sets the new pointers of the cur->prev && cur->next.
** - Free the cur elem.
*/

static void	insert_list_in_list(t_lexelem **cur,
				    t_lexlist *list,
				    t_lexlist *new_list)
{
  if ((*cur)->prev != NULL)
    {
      new_list->head->prev = (*cur)->prev;
      (*cur)->prev->next = new_list->head;
    }
  else
    list->head = new_list->head;
  if ((*cur)->next != NULL)
    (*cur)->next->prev = new_list->tail;
  else
    list->tail = new_list->tail;
  new_list->tail->next = (*cur)->next;
  free((*cur)->elem);
  free(*cur);
  (*cur) = new_list->head;
  free(new_list);
}

/*
** - Checks if there is a alias for this word.
** - If so, make a new lexlist from the str.
** - Add new_lexlist in old_lexlit at the cur pointer.
** - Error if lexlist return failure.
*/

static void	manage_potential_word(t_lexlist *list,
				      t_lexelem **cur,
				      int *flag)
{
  t_lexlist	*list_tmp;
  char		*new_str;

  if ((new_str = check_if_alias((*cur)->elem, (*cur)->elem, 0)) != NULL)
    {
      list_tmp = get_lexlist(new_str);
      if (list_tmp != NULL)
	insert_list_in_list(cur, list, list_tmp);
    }
  *flag = 0;
}

/*
** - Checks each possible lexlist elem to see if it is a alias.
** - If so, launch manage func.
*/
void		alias_lexlist(t_lexlist *list)
{
  t_lexelem	*cur;
  int		flag;

  flag = 1;
  if (list->head != NULL)
    {
      cur = list->head;
      while (cur != NULL)
	{
	  if (cur->type == REDIR && cur->next != NULL)
	    {
	      cur = cur->next;
	      if (cur->type == WORD)
		flag = 2;
	    }
	  else if (cur->type == PAR || cur->type == DELIM)
	    flag = 1;
	  else if (flag == 1 && (cur->type == WORD || cur->type == QUOTE ||
				 cur->type == DQUOTE))
	    manage_potential_word(list, &cur, &flag);
	  if (flag == 2)
	    flag = 1;
	  cur = cur->next;
	}
    }
}
