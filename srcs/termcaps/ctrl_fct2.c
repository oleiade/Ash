#include	<stdlib.h>
#include	<string.h>
#include	<dirent.h>
#include	<sys/ioctl.h>
#include	<termios.h>
#include	<term.h>
#include	<unistd.h>

#include	"42sh.h"
#include	"my.h"
#include	"termc.h"
#include	"lexer.h"
#include	"history.h"
#include	"auto.h"

t_termc		*ctrl_e(char *buff, t_termc *list, t_tutils *utils)
{
  t_com		*on;

  (void)buff;
  (void)utils;
  on = find_is_on(list);
  if (on)
    on->is_on = 0;
  aff_list(list, utils);
  return (list);
}

t_termc		*ctrl_h(char *buff, t_termc *list, t_tutils *utils)
{
 t_com		*on;

  (void)buff;
  on = find_is_on(list);
  if (on && on->prev)
    del_char(list, on->prev);
  else if (on == NULL)
  {
    tputs(utils->termcaps[1], 1, my_outc);
    my_outc(' ');
    del_char(list, list->end);
  }
  aff_list(list, utils);
  return (list);
}

t_termc		*ctrl_d(char *buff, t_termc *list, t_tutils *ut)
{
  (void)ut;
  if (!list->begin)
    char_to_list(list, buff[0]);
  return (list);
}

t_termc		*ctrl_l(char *buff, t_termc *list, t_tutils *ut)
{
  (void)buff;
  tputs(ut->termcaps[10], 1, my_outc);
  xwrite(1, PROMPT, strlen(PROMPT));
  aff_list(list, ut);
  return (list);
}
