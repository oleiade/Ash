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

/*
** - Test Arrow Keys for line edition.
*/
static	void	keys_edition(char *buff, t_termc *list)
{
  t_com		*on;

  if (buff[2] == KRIGHT)
  {
    on = find_is_on(list);
    if (on && on->next)
    {
      on->is_on = 0;
      on->next->is_on = 1;
    }
    else if (list->end)
      list->end->is_on = 0;
  }
  else if (buff[2] == KLEFT)
  {
    on = find_is_on(list);
    if (on && on->prev != NULL)
    {
      on->is_on = 0;
      on->prev->is_on = 1;
    }
    else if (on == NULL && list->end)
      list->end->is_on = 1;
  }
}

/*
** - Test Basics Keys and Chars
*/
static	t_termc	*keys(char *buff, t_termc *list, t_tutils *utils, t_link *his)
{
  t_com		*on;

  if (his && (buff[2] == KUP || buff[2] == KDOWN))
  {
    empty_line(list->nb_char, utils);
    list = str_to_list(his->data);
  }
  else if (buff[2] == KRIGHT || buff[2] == KLEFT)
    keys_edition(buff, list);
  else if (!strncmp(buff, utils->termcaps[3], READ_S) && !is_ctrl(buff[0]))
    backspace_key(utils, list);
  else if (buff[0] == 27 && buff[1] == 79)
    list = home_end_key(buff, list);
  else if (buff[0] == 27 && buff[1] == 91 && buff[2] == 51 && buff[3] == 126)
  {
    on = find_is_on(list);
    if (on)
    {
      if (on->next)
	on->next->is_on = 1;
      del_char(list, on);
    }
  }
  return (list);
}

/*
** - Main Test From Buffer
*/
t_termc		*test_buff(char *buff, t_termc *list, t_tutils *ut, t_link *his)
{
  t_com		*on;
  t_ws		ws;

  xioctl(0, TIOCGWINSZ, &ws);
  if (buff[0] == '\t' && list->nb_char + strlen(PROMPT) + 2 < ws.ws_col)
    list = auto_comp(list, ut, 0, NULL);
  else if (is_ctrl(buff[0]) || buff[0] == CTRL('k'))
    return (test_ctrl_fct(buff, list, ut));
  else if (is_good_char(buff, ut, list, &ws))
  {
    on = find_is_on(list);
    if (on == NULL)
      char_to_list(list, buff[0]);
    else
      add_to_char_list(list, on, buff[0]);
  }
  else if (buff[0] == '\n')
    unselect_list(list);
  else
    list = keys((char *)buff, list, ut, his);
  aff_list(list, ut);
  if (buff[0] == '\n' || buff[0] == CTRL('c'))
    list = prepare_to_return(list, ut, buff);
  return (list);
}

/*
** - Read Standard Input
*/
void		read_buff(char *buff)
{
  memset(buff, 0, READ_S);
  xread(0, buff, READ_S);
}
