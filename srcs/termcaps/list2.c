#include	<stdlib.h>
#include	<string.h>
#include	<dirent.h>
#include	<sys/ioctl.h>
#include	<term.h>
#include	<unistd.h>

#include	"42sh.h"
#include	"my.h"
#include	"lexer.h"
#include	"termc.h"

/*
** - Put cursor to the line begin
*/
void		begin_line(t_tutils *utils)
{
  int		i;

  i = strlen(PROMPT);
  tputs(utils->termcaps[7], 1, my_outc);
  while (i)
    {
      tputs(utils->termcaps[2], 1, my_outc);
      i--;
    }
}

/*
** - Explicit function
*/
void		aff_list(t_termc *list, t_tutils *utils)
{
  int		c;
  t_com		*buff;
  t_ws		ws;

  xioctl(0, TIOCGWINSZ, &ws);
  c =  -1;
  buff = list->begin;
  begin_line(utils);
  while (++c < list->nb_char && (unsigned)c < ws.ws_col - strlen(PROMPT))
    {
      if (buff->is_on)
	tputs(utils->termcaps[4], 1, my_outc);
      my_outc(buff->c);
      if (buff->is_on)
	tputs(utils->termcaps[5], 1, my_outc);
      buff = buff->next;
    }
  if (find_is_on(list) == NULL && list->is_ready == 0)
    {
      tputs(utils->termcaps[4], 1, my_outc);
      my_outc(' ');
      tputs(utils->termcaps[5], 1, my_outc);
    }
  else
    my_outc(' ');
}

/*
** - Make list from string
*/
t_termc		*str_to_list(char *str)
{
  int		i;
  t_termc	*list;

  list = init_char_list();
  i = 0;
  while (str[i])
    {
      char_to_list(list, str[i]);
      i++;
    }
  return (list);
}

/*
** - Put char to list end
*/
void		char_to_list(t_termc *list, char c)
{
  t_com		*new;

  new = xmalloc(sizeof(*new));
  new->next = NULL;
  new->c = c;
  new->is_on = 0;
  if (list->end)
    {
      list->end->next = new;
      new->prev = list->end;
      list->end = new;
    }
  else
    {
      list->nb_char = 0;
      list->begin = new;
      list->end = new;
      new->prev = NULL;
    }
  list->nb_char++;
}

/*
** - Add char after the t_com *com position in list
*/
void		add_to_char_list(t_termc *list, t_com *com, char c)
{
  t_com		*new;

  new = xmalloc(sizeof(*new));
  new->c = c;
  new->is_on = 0;
  if (com->prev)
    {
      com->prev->next = new;
      new->prev = com->prev;
    }
  else
    {
      list->begin = new;
      new->prev = NULL;
    }
  new->next = com;
  com->prev = new;
  list->nb_char++;
}
