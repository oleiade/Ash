/*
** list_to_tab.c for minishell2 in /u/all/gsell_f/cu/rendu/c/minishell2
** 
** Made by francois-xavier gsell
** Login   <gsell_f@epitech.net>
** 
** Started on  Tue Feb  9 10:41:41 2010 francois-xavier gsell
** Last update Sat May 22 14:27:35 2010 hugo cuvillier
*/

#include	<stdlib.h>
#include	<string.h>
#include	<dirent.h>
#include	<unistd.h>

#include	"my.h"
#include	"42sh.h"

int		sizeofelem(t_sllist *list)
{
  int		size;

  size = strlen(list->name);
  size += strlen(list->data);
  return (sizeof(char) * (size + 2));
}

int		nb_list(t_sllist *list)
{
  int		i;

  i = 0;
  while (list != 0)
    {
      list = list->next;
      i++;
    }
  return (i + 1);
}

int		free_list_tab(char **tab)
{
  int		i;

  i = 0;
  while (tab[i] != NULL)
    {
      free(tab[i]);
      i++;
    }
  free(tab);
  return (0);
}

char		**list_to_tab(t_sllist *list)
{
  char		**tab;
  int		i;

  i = 0;
  tab = xmalloc(sizeof(char *) * nb_list(list));
  while (list != NULL)
    {
      tab[i] = xmalloc(sizeofelem(list));
      memset(tab[i], 0, sizeofelem(list));
      strcpy(tab[i], list->name);
      strcat(tab[i], "=");
      strcat(tab[i], list->data);
      list = list->next;
      i++;
    }
  tab[i] = 0;
  return (tab);
}
