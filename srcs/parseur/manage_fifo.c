#include	<stdlib.h>
#include	<dirent.h>
#include	<string.h>
#include	<unistd.h>

#include	"42sh.h"

/*
** - Add an elem to the fifo->cur pointer depending on the
**   flag value (down ^ next).
*/

static void	add_to_fifo(t_fifo *fifo, int *is_next)
{
  t_fifo_elem	*new;

  new = xmalloc(sizeof(*new));
  if (*is_next)
    {
      if (fifo->cur == NULL)
	fifo->begin = new;
      new->prev = fifo->cur;
      if (fifo->cur != NULL)
	fifo->cur->next = new;
      if (new->prev != NULL)
	new->up = new->prev->up;
    }
  else
    {
      *is_next = NEXT;
      new->up = fifo->cur;
      fifo->cur->down = new;
    }
  new->data.return_val = EXIT_FAILURE;
  fifo->cur = new;
}

/*
** - Sets the redirections flags && file name for a group.
*/

static void	manage_down_in_out(t_fifo *list)
{
  t_fifo_elem	*tmp;

  tmp = list->cur->down;
  while (tmp != NULL)
    {
      if (!tmp->data.flag[IN] && list->cur->data.flag[IN])
	{
	  tmp->data.flag[IN] = list->cur->data.flag[IN];
	  if (list->cur->data.file_name[IN])
	    tmp->data.file_name[IN] = strdup(list->cur->data.file_name[IN]);
	}
      if (!tmp->data.flag[OUT] && list->cur->data.flag[OUT])
	{
	  if (F_ISSIOUT(list->cur->data.flag[OUT]) && tmp->prev != NULL)
	    tmp->data.flag[OUT] = F_DBOUT;
	  else
	    tmp->data.flag[OUT] = list->cur->data.flag[OUT];
	  if (list->cur->data.file_name[OUT])
	    tmp->data.file_name[OUT] = strdup(list->cur->data.file_name[OUT]);
	}
      tmp = tmp->next;
    }
}

/*
** - Sets the groups flags and heritage.
*/

static void	manage_parentship(t_fifo *list)
{
  list->cur = list->begin;
  while (list->cur != NULL)
    {
      if (list->cur->down != NULL)
	{
	  manage_down_in_out(list);
	  list->cur = list->cur->down;
	}
      else if (list->cur != NULL)
	{
	  if (list->cur->next == NULL && list->cur->up != NULL)
	    list->cur = list->cur->up->next;
	  else
	    list->cur = list->cur->next;
	}
    }
}

/*
** - Manage the parenthesis creation process.
*/

static int	manage_par(t_fifo *list, t_lexelem **stpt)
{
  if ((*stpt)->elem[0] == '(')
    {
      *stpt = (*stpt)->next;
      if (create_fifo(list, stpt, SUB) == EXIT_FAILURE)
	return (EXIT_FAILURE);
    }
  else if ((*stpt)->elem[0] == ')')
    {
      list->cur = list->cur->up;
      *stpt = (*stpt)->next;
      return (EXIT_SUCCESS);
    }
  return (EXIT_NOTHING);
}

/*
** - Creates the LL tree for the parser.
*/

int		create_fifo(t_fifo *list, t_lexelem **stpt, int flag)
{
  int		return_buf;

  return_buf = 0;
  while (*stpt != NULL)
    {
      if (return_buf != NO_ADD)
	add_to_fifo(list, &flag);
      if ((*stpt)->type == PAR)
	if ((return_buf = manage_par(list, stpt)) != EXIT_NOTHING)
	  return (return_buf);
      set_argv(list->cur, *stpt);
      if (set_redir(list->cur, *stpt) == EXIT_FAILURE)
	return (EXIT_FAILURE);
      return_buf = set_stpt(stpt);
    }
  list->end = list->cur;
  manage_parentship(list);
  return (EXIT_SUCCESS);
}
