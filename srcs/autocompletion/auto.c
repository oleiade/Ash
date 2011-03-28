#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include	<sys/types.h>
#include	<ctype.h>
#include	<dirent.h>
#include	<termios.h>
#include	<sys/ioctl.h>
#include	<term.h>

#include	"my.h"
#include	"42sh.h"
#include	"lexer.h"
#include	"termc.h"
#include	"auto.h"
#include	"lexer.h"


int		is_path(t_termc *com)
{
  t_lexlist	*lex;

  lex = get_lexlist(list_to_char(com));
  if (lex && com)
  {
    if (lex->keys == 0)
      return (0);
    else
    {
      if (lex->keys > 1 && lex->tail->type == WORD && lex->tail->prev->type == WORD)
	return (1);
      else if (lex->tail->type == WORD && com->end->c == ' ')
	return (1);
      else if (lex->tail->type != WORD)
	return (0);
    }
  }
  if (lex)
    free_lexlist(lex, 1);
  return (0);
}

/*int		is_path(t_termc *command)
{
  t_com		*buff;

  buff = command->begin;
  if (buff && buff->c == '.')
    return (1);
  buff = command->end;
  while (buff)
  {
    if (buff->c == ' ')
      return (1);
    buff = buff->prev;
  }
  return (0);
}*/

void		echo_completion(t_termc *command, t_tutils *utils, t_list *comp)
{
  char		buff[10];

  memset(buff, 0, 10);
  unselect_list(command);
  aff_list(command, utils);
  command->is_ready = 0;
  my_outc('\n');
  if (comp->size > 100)
  {
    my_outs(MAX_CAP1);
    sprintf(buff, "%d ", comp->size);
    my_outs(buff);
    my_outs(MAX_CAP2);
    xread(0, buff, 10);
    my_outc('\n');
  }
  if (buff != NULL)
    if (buff[0] != 'n')
      aff_tty(list_to_double_tab(comp), comp->size);
    tputs(utils->termcaps[7], 1, my_outc);
  xwrite(1, PROMPT, strlen(PROMPT));
}

t_termc		*my_listcat(t_termc *com, t_list *list)
{
  t_com		*buff_c;
  t_com		*buff;
  int		i;

  i = 0;
  buff_c = com->end;
  if (com->begin && com->begin->c == '.')
    buff_c = com->begin;
  else
  {
    while (buff_c && (isupper(buff_c->c) || islower(buff_c->c) ||
	   buff_c->c == '-' || buff_c->c == '_' || buff_c->c == '/') &&
	   buff_c->c != ' ')
      buff_c = buff_c->prev;
    if (buff_c && buff_c->next)
      buff_c = buff_c->next;
  }
  while ((buff = buff_c))
  {
    buff_c = buff_c->next;
    del_char(com, buff);
  }
  while (list->head->data[i])
  {
    char_to_list(com, list->head->data[i]);
    i++;
  }
  return (com);
}

void		extract_utils(t_list *list)
{
  t_link	*buff;
  char		*str;
  char		*new;
  int		i;

  buff = list->head;
  while (buff)
  {
    str = buff->data;
    i = strlen(str);
    while (i && str[i] != '/')
      i--;
    if (i == (int)(strlen(str) - 1))
    {
      i--;
      while (i && str[i] != '/')
	i--;
    }
    i++;
    if (i == 1 || i == (int)strlen(str))
      i = 0;
    new = strdup(str + i);
    buff->data = new;
    buff = buff->next;
  }
}

t_termc		*auto_comp(t_termc *com, t_tutils *ut, int fl, t_sllist *myenv)
{
  t_list	*new_binary;
  t_termc	*com_buff;
  static t_list	*binary = NULL;

  new_binary = NULL;
  if (fl == DEL && binary != NULL)
    freemylist(binary);
  else
  {
    if (binary == NULL)
      binary = parse_ex(my_wordlist(my_getenv("PATH", myenv), ':', ':'));
    else
    {
      if (is_path(com))
      {
	if (com == (com_buff = manage_path(com, ut, parse_path(com))))
	  return (com_buff);
      }
      else
	if ((new_binary = select_exec(binary, list_to_char(com))) != NULL)
	  if ((com_buff = manage_auto(new_binary, com, ut)) != com)
	    return (com_buff);
    }
  }
  return (com);
}
