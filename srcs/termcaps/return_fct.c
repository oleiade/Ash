#include	<stdlib.h>
#include	<string.h>
#include	<dirent.h>
#include	<unistd.h>

#include	"42sh.h"
#include	"my.h"
#include	"lexer.h"
#include	"termc.h"
#include	"auto.h"
#include	"history.h"

static	char	*return_ctrl_c(t_tutils *utils, t_termc *list, t_list *hist)
{
  char		*buff;

  restore_mode(utils, NULL);
  buff = xmalloc(2 * sizeof(*buff));
  strcpy(buff, "");
  make_res(list, hist);
  return (buff);
}

static	char	*return_ctrl_d(t_termc *list, t_tutils *utils)
{
  unselect_list(list);
  aff_list(list, utils);
  my_outc('\n');
  restore_mode(utils, NULL);
  return (0);
}

char		*rtn_fct(char *b, t_tutils *ut, t_termc *list, t_list *hist)
{
  if (list && list->begin && list->begin->c == CEOF)
    return (return_ctrl_d(list, ut));
  else if (list == NULL && b[0] == CTRL('c'))
    return (return_ctrl_c(ut, list, hist));
  return (b);
}
