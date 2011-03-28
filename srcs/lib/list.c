/*
** list.c for minishell2 in /u/all/gsell_f/cu/rendu/c/minishell2
** 
** Made by francois-xavier gsell
** Login   <gsell_f@epitech.net>
** 
** Started on  Tue Feb  9 10:41:46 2010 francois-xavier gsell
** Last update Sat May 22 14:27:55 2010 hugo cuvillier
*/

#include	<stdlib.h>
#include	<string.h>
#include	<dirent.h>
#include	<unistd.h>

#include	"my.h"
#include	"42sh.h"

t_sllist		*add_to_list(t_sllist **list, char *name, char *data)
{
  t_sllist	*new;

  new = xmalloc(sizeof(*new));
  new->next = *list;
  *list = new;
  if (name != NULL)
    {
      new->name = xmalloc(sizeof(*name) * (strlen(name) + 1));
      strcpy(new->name, name);
    }
  if (data != NULL)
    {
      new->data = xmalloc(sizeof(*data) * (strlen(data) + 1));
      strcpy(new->data, data);
    }
  return (new);
}

t_sllist		*found_in_list(t_sllist *list, char *name)
{
  t_sllist	*tmp;

  tmp = list;
  while (tmp != NULL)
    {
      if (strcmp(tmp->name, name) == 0)
	return (tmp);
      tmp = tmp->next;
    }
  return (NULL);
}
