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

static const struct s_ctrl	ctrl[26] = {
  {'a', CA, ctrl_a},
  {'b', CB, NULL},
  {'c', CINTR, NULL},
  {'d', CEOF, ctrl_d},
  {'e', CE, ctrl_e},
  {'f', CF, NULL},
  {'g', CG, NULL},
  {'h', CBS, ctrl_h},
  {'i', CI, NULL},
  {'k', CK, ctrl_k},
  {'l', CNL, ctrl_l},
  {'m', CM, NULL},
  {'n', CN, NULL},
  {'o', CDISCARD, NULL},
  {'p', CP, NULL},
  {'q', CSTART, NULL},
  {'r', CREPRINT, NULL},
  {'s', CSTOP, NULL},
  {'t', CT, NULL},
  {'u', CKILL, NULL},
  {'v', CLNEXT, NULL},
  {'w', CWERASE, NULL},
  {'x', CX, NULL},
  {'y', CDSUSP, NULL},
  {'z', CSUSP, NULL},
  {0, 0, NULL}
};

int		is_ctrl(char b)
{
  int		i;

  i = 0;
  while (ctrl[i].value != 0 && ctrl[i].value != b)
    i++;
  if (ctrl[i].ptr == NULL)
    return (0);
  return (ctrl[i].value);
}

void		ctrl_c()
{
  my_outc('\n');
}

t_termc		*ctrl_k(char *buff, t_termc *list, t_tutils *utils)
{
  int		i;
  t_com		*on;
  t_com		*on_buff;

  (void)buff;
  i = 0;
  empty_line(list->nb_char, utils);
  on = find_is_on(list);
  while (on)
  {
    on_buff = on;
    on = on->next;
    del_char(list, on_buff);
  }
  aff_list(list, utils);
  return (list);
}

t_termc		*ctrl_a(char *buff, t_termc *list, t_tutils *utils)
{
  t_com		*on;

  (void)buff;
  (void)utils;
  on = find_is_on(list);
  if (on)
    on->is_on = 0;
  if (list->begin)
    list->begin->is_on = 1;
  aff_list(list, utils);
  return (list);
}

/*
** - Ctrl key test
*/
t_termc		*test_ctrl_fct(char *buff, t_termc *list, t_tutils *ut)
{
  int		i;

  i = 0;
  while (ctrl[i].value != 0 && ctrl[i].value != buff[0])
    i++;
  if (ctrl[i].value != 0 && ctrl[i].ptr != NULL)
    return (ctrl[i].ptr(buff, list, ut));
  return (list);
}
