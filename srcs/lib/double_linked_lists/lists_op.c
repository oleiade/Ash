/*
** dlists_op.c for dlists_op in /u/all/crevon_t/cu/rendu/lib/my/double_lists
** 
** Made by theo crevon
** Login   <crevon_t@epitech.net>
** 
** Started on  Tue Jan 12 13:10:08 2010 theo crevon
** Last update Fri Feb 12 17:37:48 2010 nathan mustaki
*/

#include	<stdlib.h>
#include	<dirent.h>
#include	<string.h>
#include	<stdio.h>

#include	"my.h"

int		print_list(t_list *list)
{
  t_link	*new_elem;

  new_elem = NULL;
  if (list == NULL)
    return (-1);
  new_elem = list->head;
  while (new_elem != NULL)
    {
      fputs(new_elem->data, stdout);
      new_elem = new_elem->next;
      putc('\n', stdout);
    }
  return (0);
}

char		*get_xlink(t_list *list, int x)
{
  t_link	*new_elem;
  int		x_intra;

  x_intra = 1;
  new_elem = NULL;
  if (list == NULL)
    return (NULL);
  else if (x <= 0 || x > list->size)
    return (NULL);
  new_elem = list->head;
  while (x_intra < x)
    {
      new_elem = new_elem->next;
      x_intra++;
    }
  return (new_elem->data);
}

char		*update_link(t_list *list, int pos, char *str)
{
  t_link	*new_elem;
  int		pos_intra;

  pos_intra = 1;
  new_elem = NULL;
  if (list == NULL)
    return (NULL);
  else if (pos <= 0 || pos > list->size)
    return (NULL);
  new_elem = list->head;
  while (pos_intra < pos)
    {
      new_elem = new_elem->next;
      pos_intra++;
    }
  free(new_elem->data);
  new_elem->data = xmalloc(strlen(str) * sizeof(char));
  strcpy(new_elem->data, str);
  return (new_elem->data);

}
