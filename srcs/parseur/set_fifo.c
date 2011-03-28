#include	<stdlib.h>
#include	<dirent.h>
#include	<string.h>
#include	<unistd.h>

#include	"42sh.h"

static int	count_ac(t_lexelem *stpt)
{
  int		res;

  res = 0;
  while (stpt != NULL)
    {
      if (stpt->type == DELIM || stpt->type == PAR)
	return (res);
      else if (stpt->type == REDIR)
	stpt = stpt->next;
      else if (stpt->type == WORD || stpt->type == QUOTE ||
	       stpt->type == DQUOTE)
	res++;
      if (stpt != NULL)
	stpt = stpt->next;
    }
  return (res);
}

void		set_argv(t_fifo_elem *elem, t_lexelem *stpt)
{
  int		ac;
  int		i;

  i = 0;
  ac = count_ac(stpt);
  if (ac)
    elem->data.argv = xmalloc((ac + 1) * sizeof(char *));
  while (i < ac && stpt != NULL)
    {
      if (stpt->type == REDIR)
	{
	  stpt = stpt->next;
	  if (stpt->type == AND)
	    stpt = stpt->next;
	}
      else if (stpt->type == WORD || stpt->type == QUOTE ||
               stpt->type == DQUOTE)
	{
	  elem->data.argv[i] = stpt->elem;
	  i++;
	}
      if (stpt != NULL)
	stpt = stpt->next;
    }
  if (ac)
    elem->data.argv[i] = NULL;
}

/*
** - Manages the parenthesis in order to add the correct redir values.
*/

static void	manage_open_par(t_lexelem **stpt)
{
  int		par;

  par = 0;
  par++;
  while (*stpt != NULL && par)
    {
      if ((*stpt)->type == PAR && (*stpt)->elem[0] == '(')
	par++;
      else if ((*stpt)->type == PAR && (*stpt)->elem[0] == ')')
	par--;
      (*stpt) = (*stpt)->next;
    }
}

/*
** - Manages the redirection in a file.
*/

static int	manage_set_redir(t_fifo_elem *elem, t_lexelem **stpt)
{
  int		redir_type;

  redir_type = set_redir_flag(elem, *stpt);
  if (redir_type < 0)
    return (EXIT_FAILURE);
  (*stpt) = (*stpt)->next;
  if ((*stpt)->type == AND)
    {
      elem->data.flag[ERR] = 1;
      (*stpt) = (*stpt)->next;
    }
  elem->data.file_name[redir_type] = (*stpt)->elem;
  return (EXIT_SUCCESS);
}

/*
** - Sets the redirections && condition && argv && params of
**   a fifo_elem.
*/

int		set_redir(t_fifo_elem *elem, t_lexelem *stpt)
{
  while (stpt != NULL)
    {
      if (stpt->type == PAR && stpt->elem[0] == '(')
	manage_open_par(&stpt);
      else if (stpt->type == PAR && stpt->elem[0] == ')')
	break;
      else if (stpt->type == DELIM || stpt->type == AND)
	{
	  set_delim_flag(elem, stpt);
	  stpt = stpt->next;
	  return (EXIT_SUCCESS);
	}
      else if (stpt->type == REDIR)
	if (manage_set_redir(elem, &stpt) == EXIT_FAILURE)
	  return (EXIT_FAILURE);
      if (stpt != NULL)
	stpt = stpt->next;
    }
  return (EXIT_SUCCESS);
}
