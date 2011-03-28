#include	<stdlib.h>
#include	<string.h>
#include	<sys/types.h>
#include	<dirent.h>

#include	"my.h"
#include	"42sh.h"
#include	"lexer.h"
#include	"termc.h"
#include	"auto.h"

int		sum_space(int *tab, int len)
{
  int		len_total;
  int		i;

  i = 0;
  len_total = 0;
  while (i <= len)
    {
      len_total += tab[i];
      i++;
    }
  len_total -= 2;
  return (len_total);
}

int		*calc_tab_space(char **tab, int len)
{
  int		*len_tab;
  int		i;

  i = 0;
  len_tab = xmalloc((1 + len) * sizeof(*len_tab));
  while (i <= len)
    {
      len_tab[i] = strlen(tab[i]) + 2;
      i++;
    }
  return (len_tab);
}

int		calc_len(char **tab, int i)
{
  int		len_tot;

  len_tot = 0;
  while (i >= 0)
    {
      len_tot += strlen(tab[i]) + 2;
      i--;
    }
  return (len_tot);
}

char		**list_to_double_tab(t_list *list)
{
  char		**tab;
  int		i;
  t_link	*buff;

  buff = list->head;
  i = 0;
  tab = xmalloc((list->size + 2) * sizeof(*tab));
  while (buff)
    {
      tab[i] = xmalloc((strlen(buff->data) + 1) * sizeof(**tab));
      strcpy(tab[i], buff->data);
      i++;
      buff = buff->next;
    }
  tab[i] = xmalloc(2 * sizeof(**tab));
  tab[i + 1] = NULL;
  return (tab);
}
