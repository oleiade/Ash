#include	<stdlib.h>
#include	<dirent.h>
#include	<string.h>
#include	<unistd.h>

#include	"42sh.h"

/*
** - Free the LL parser list.
*/

void		free_fifo(t_fifo *fifo)
{
  t_fifo_elem	*tmp;
  t_fifo_elem	*next;

  tmp = NULL;
  if (fifo != NULL)
    tmp = fifo->cur;
  while (tmp != NULL)
    {
      next = tmp->next;
      if (tmp->down != NULL)
	{
	  fifo->cur = tmp->down;
	  free_fifo(fifo);
	}
      free_argv(tmp->data.argv);
      free(tmp);
      tmp = next;
    }
}

/*
** - Sets the appropriate address of the lexlist pointer.
*/

int		set_stpt(t_lexelem **stpt)
{
  while (*stpt != NULL)
    {
      if ((*stpt)->type == DELIM)
	{
	  *stpt = (*stpt)->next;
	  return (EXIT_SUCCESS);
	}
      else if ((*stpt)->type == PAR)
	return (NO_ADD);
      if (*stpt != NULL)
	*stpt = (*stpt)->next;
    }
  return (EXIT_SUCCESS);
}
