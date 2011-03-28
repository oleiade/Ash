#include	<stdlib.h>
#include	<dirent.h>
#include	<string.h>
#include	<stdio.h>
#include	<unistd.h>

#include	"42sh.h"

static int	set_redir_flag_out(t_fifo_elem *elem, t_lexelem *stpt)
{
  if (elem->data.flag[OUT])
    {
      fprintf(stderr, ERR_OUTPUT_RED);
      return (-1);
    }
  if (!strcmp(stpt->elem, ">>"))
    elem->data.flag[OUT] = F_DBOUT;
  else
    elem->data.flag[OUT] = F_SIOUT;
  if (stpt->next != NULL)
    if (stpt->next->type == AND)
      elem->data.flag[ERR] = 1;
  return (OUT);
}

static int	set_redir_flag_in(t_fifo_elem *elem, t_lexelem *stpt)
{
  if (elem->data.flag[IN])
    {
      fprintf(stderr, ERR_INPUT_RED);
      return (-1);
    }
  if (!strcmp(stpt->elem, "<<"))
    elem->data.flag[IN] = F_DBIN;
  else
    elem->data.flag[IN] = F_SIIN;
  if (stpt->next != NULL)
    if (stpt->next->type == AND)
      elem->data.flag[ERR] = 1;
  return (IN);
}

int		set_redir_flag(t_fifo_elem *elem, t_lexelem *stpt)
{
  int		redir_type;

  if (!strcmp(stpt->elem, ">>") || !strcmp(stpt->elem, ">"))
    redir_type = set_redir_flag_out(elem, stpt);
  else
    redir_type = set_redir_flag_in(elem, stpt);
  return (redir_type);
}

void		set_delim_flag(t_fifo_elem *elem, t_lexelem *stpt)
{
  if (!strcmp(stpt->elem, "|"))
    {
      elem->data.flag[OUT] = F_PIPE;
      if (stpt->next != NULL)
	if (stpt->next->type == AND)
	  elem->data.flag[ERR] = 1;
    }
  else if (!strcmp(stpt->elem, "&&"))
    elem->data.flag[SEC] = F_SECOK;
  else if (!strcmp(stpt->elem, "||"))
    elem->data.flag[SEC] = F_SECERR;
  else if (!strcmp(stpt->elem, ";"))
    elem->data.flag[SEC] = F_SEC;
  else if (!strcmp(stpt->elem, "&"))
    {
      if (stpt->prev != NULL)
	if (stpt->prev->type != REDIR &&
	    stpt->prev->type != DELIM)
	  elem->data.flag[DSYNC] = 1;
    }
}
