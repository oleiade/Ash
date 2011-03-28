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
#include	"get_next_line.h"

/*
** - Make final string from list and free.
*/
char		*make_res(t_termc *list, t_list *history)
{
  char		*res;

  res = list_to_char(list);
  if (list && list->nb_char)
    free_char_list(list);
  if (strlen(res) && res && history)
  {
    if (history->tail && strcmp(history->tail->data, res))
      history = add_stdin_to_history(res, history);
    else if (history->tail == NULL)
      history = add_stdin_to_history(res, history);
  }
  return (res);
}

/*
** - Test keys for History
*/
t_link		*test_histo(char *buff, t_link *histo_b)
{
  if (buff[2] == KUP && histo_b->previous)
    histo_b = histo_b->previous;
  else if (histo_b && buff[2] == KDOWN && histo_b->next)
    histo_b = histo_b->next;
  return (histo_b);
}

/*
** - Restore Old List
*/
void		old(t_termc **list, t_tutils *ut, t_link **h_b, t_termc *cur)
{
  empty_line((*list)->nb_char, ut);
  *list = cur;
  aff_list(*list, ut);
  *h_b = NULL;
}

/*
** - Save Current List
*/
void		save_cur(t_termc *list, t_termc **cur, t_list *h, t_link **h_b)
{
  *h_b = h->tail;
  *cur = list;
}

/*
** - Main termcap function
** -
** - Prepare the term for termcaps acts,
** - make all lists and all stuffs.
*/
char		*termcaps(t_tutils *utils, t_list *history)
{
  char		*buff;
  t_termc	*list;
  t_link	*histo_b;
  t_termc	*cur_save;

  cur_save = NULL;
  list = init_char_list();
  init_func(list, utils);
  histo_b = NULL;
  buff = xmalloc(READ_S * sizeof(*buff));
  while (buff[0] != '\n' && buff[0] != CTRL('c'))
  {
    read_buff(buff);
    if (history && buff[2] == KUP && histo_b == NULL)
      save_cur(list, &cur_save, history, &histo_b);
    else if (history && buff[2] == KDOWN && histo_b == history->tail)
      old(&list, utils, &histo_b, cur_save);
    else if (histo_b)
      histo_b = test_histo(buff, histo_b);
    list = test_buff(buff, list, utils, histo_b);
    if ((buff = rtn_fct(buff, utils, list, history)) == 0 || !strcmp(buff, ""))
      return (buff);
  }
  restore_mode(utils, buff);
  return (make_res(list, history));
}
