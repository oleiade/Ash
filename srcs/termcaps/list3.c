#include	<stdlib.h>
#include	<dirent.h>

#include	"my.h"
#include	"lexer.h"
#include	"termc.h"

/*
** - Free char list
*/
void		free_char_list(t_termc *list)
{
  t_com		*buff;
  t_com		*com;

  if (list)
  {
    buff = list->begin;
    while (buff)
    {
      com = buff;
      buff = buff->next;
      free(com);
    }
  }
}
