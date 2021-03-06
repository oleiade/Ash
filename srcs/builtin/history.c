#include	<unistd.h>
#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include	<dirent.h>

#include	"my.h"
#include	"42sh.h"
#include	"termc.h"
#include	"auto.h"

t_list		*update_history(t_list *history)
{
  static t_list	*histo_buff = NULL;

  if (history != NULL)
    histo_buff = history;
  return (histo_buff);
}

int		built_in_history(char **argv, t_sllist **myenv)
{
  t_list	*histo;
  int		nb;

  (void)myenv;
  histo = update_history(NULL);
  if (histo != NULL)
  {
    if (argv[1])
      nb = atoi(argv[1]);
    else
      nb = 20;
    if (nb >= histo->size)
      nb = histo->size;
    aff_tty(list_to_double_tab(histo), nb);
  }
  else
  {
    printf("%s", ERR_BUILTIN_HISTORY);
    return (EXIT_FAILURE);
  }
  return (EXIT_SUCCESS);
}
