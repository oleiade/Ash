#include	<stdlib.h>
#include	<string.h>
#include	<dirent.h>
#include	<sys/ioctl.h>
#include	<termios.h>
#include	<fcntl.h>
#include	<term.h>
#include	<unistd.h>

#include	"42sh.h"
#include	"my.h"
#include	"termc.h"
#include	"lexer.h"
#include	"history.h"
#include	"auto.h"

t_termc		*prepare_to_return(t_termc *list, t_tutils *ut, char *buff)
{
  unselect_list(list);
  aff_list(list, ut);
  my_outc('\n');
  if (buff[0] == CTRL('c'))
  {
    free_char_list(list);
    list = NULL;
  }
  return (list);
}

int		is_good_char(char *buff, t_tutils *ut, t_termc *list, t_ws *ws)
{
  if (buff[0] != '\n' && !buff[1] && !buff[2] && buff[0] != CTRL('c') &&
    strncmp(buff, ut->termcaps[3], READ_S) && !is_ctrl(buff[0]) &&
    list->nb_char < BUFF_LIMIT &&
    list->nb_char + strlen(PROMPT) + 2 < ws->ws_col)
    return (1);
  return (0);
}

void		backspace_key(t_tutils *utils, t_termc *list)
{
  t_com		*on;

  on = find_is_on(list);
  if (on && on->prev)
    del_char(list, on->prev);
  else if (on == NULL)
  {
    tputs(utils->termcaps[1], 1, my_outc);
    my_outc(' ');
    del_char(list, list->end);
  }
}

t_termc		*home_end_key(char *buff, t_termc *list)
{
  t_com		*on;

  if (buff[2] == 70 || buff[2] == 72)
  {
    on = find_is_on(list);
    if (on)
      on->is_on = 0;
  }
  if (buff[2] == 72)
    if (list->begin)
      list->begin->is_on = 1;
    return (list);
}
