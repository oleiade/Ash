#include	<stdlib.h>
#include	<stdio.h>
#include	<dirent.h>
#include	<string.h>
#include	<unistd.h>

#include	"42sh.h"

static int	verif_manage_red(t_lexelem **stpt)
{
  if ((*stpt)->type == AND && (*stpt)->next != NULL)
    (*stpt) = (*stpt)->next;
  if ((*stpt)->type != WORD && (*stpt)->type != DQUOTE &&
      (*stpt)->type != QUOTE)
    {
      fprintf(stderr, ERR_MISSING_REDIR_NAME);
      return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}

static int	verif_red(t_lexelem *stpt)
{
  while (stpt != NULL)
    {
      if (stpt->type == REDIR)
	{
	  stpt = stpt->next;
	  if (stpt == NULL)
            {
              fprintf(stderr, ERR_MISSING_REDIR_NAME);
              return (EXIT_FAILURE);
            }
          else if (verif_manage_red(&stpt) == EXIT_FAILURE)
	    return (EXIT_FAILURE);
        }
      if (stpt != NULL)
        stpt = stpt->next;
    }
  return (EXIT_SUCCESS);
}

static int	is_word(t_lexelem *elem)
{
  if (elem->type == WORD ||
      elem->type == QUOTE ||
      elem->type == DQUOTE ||
      elem->type == PAR)
    return (1);
  return (0);
}

static int	verif_syn(t_lexelem *elem)
{
  if (elem != NULL)
    {
      if (!is_word(elem) && elem->next == NULL)
        {
          fprintf(stderr, "%s", ERR_DELIM);
          return (EXIT_FAILURE);
        }
      while (elem->next != NULL)
        {
          if (((!is_word(elem) && !is_word(elem->next)
		&& elem->next->type != REDIR) &&
	      (elem->type != AND && elem->next->type != AND)) ||
	      (is_word(elem) && elem->next->type == DELIM &&
	       elem->next->elem[0] != ';' &&
	       elem->next->next == NULL))
            {
              fprintf(stderr, "%s", ERR_DELIM);
              return (EXIT_FAILURE);
            }
          elem = elem->next;
        }
      return (EXIT_SUCCESS);
    }
  return (EXIT_FAILURE);
}

int		verif_list(t_lexelem *elem)
{
  if (verif_red(elem) == EXIT_FAILURE ||
      verif_par(elem) == EXIT_FAILURE ||
      verif_syn(elem) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
