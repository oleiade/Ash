#include	<stdio.h>
#include	<dirent.h>
#include	<string.h>
#include	<unistd.h>

#include	"42sh.h"
#include	<stdlib.h>
#include	<stdio.h>
#include	<dirent.h>
#include	<string.h>
#include	<unistd.h>

#include	"42sh.h"

static int	manage_verif_par(t_lexelem *stpt, int par)
{
  if (!strcmp(stpt->elem, "("))
    {
      par++;
      if (stpt->next != NULL)
	if (!strcmp(stpt->next->elem, ")"))
	  {
	    fprintf(stderr, "%s", ERR_BADPAR);
	    return (-1);
	  }
    }
  else
    {
      par--;
      if (stpt->next != NULL)
	if (!strcmp(stpt->next->elem, "("))
	  {
	    fprintf(stderr, "%s", ERR_BADPAR);
	    return (-1);
	  }
    }
  return (par);
}

int		verif_par(t_lexelem *stpt)
{
  int		par;

  par = 0;
  while (stpt != NULL)
    {
      if (stpt->type == PAR)
	if ((par = manage_verif_par(stpt, par)) < 0)
	  return (EXIT_FAILURE);
      stpt = stpt->next;
    }
  if (par)
    {
      fprintf(stderr, ERR_UNMAPAR);
      return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}
