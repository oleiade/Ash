#include	<stdlib.h>
#include	<dirent.h>
#include	<unistd.h>

#include	"42sh.h"

/*
** - Manage the delimitors && , || , ; to check if this elem
**   needs to be executed.
*/

int		manage_delim(t_fifo_elem *cur)
{
  if (cur->prev != NULL && !F_ISSEC(cur->prev->data.flag[SEC]))
    {
      if (((F_ISSECOK(cur->prev->data.flag[SEC]) &&
	    cur->prev->data.return_val != EXIT_SUCCESS)) ||
	  ((F_ISSECERR(cur->prev->data.flag[SEC]) &&
	    cur->prev->data.return_val == EXIT_SUCCESS)))
	{
	  if (F_ISSECERR(cur->prev->data.flag[SEC]) &&
	      cur->prev->data.return_val == EXIT_SUCCESS)
	    {
	      if (F_ISSECERR(cur->data.flag[SEC]))
		cur->data.return_val = EXIT_SUCCESS;
	      else
		cur->data.return_val = EXIT_FAILURE;
	    }
	  else
	    cur->data.return_val = EXIT_FAILURE;
	  return (EXIT_FAILURE);
	}
    }
  return (EXIT_SUCCESS);
}
