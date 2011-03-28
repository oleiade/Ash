#include	<stdlib.h>
#include	<string.h>
#include	<unistd.h>
#include	<dirent.h>
#include	<sys/types.h>

#include	"my.h"
#include	"lexer.h"
#include	"termc.h"
#include	"auto.h"

void		sort_list(t_list *list, t_list *path)
{
  t_link	*buff1;
  char		*str;
  int		i;

  i = list->size;
  while (i)
    {
      buff1 = list->head;
      while (buff1)
	{
	  if (buff1->next && strcmp(buff1->data, buff1->next->data) > 0)
	    {
	      str = buff1->data;
	      buff1->data = buff1->next->data;
	      buff1->next->data = str;
	    }
	  buff1 = buff1->next;
	}
      i--;
    }
  freemylist(path);
}
