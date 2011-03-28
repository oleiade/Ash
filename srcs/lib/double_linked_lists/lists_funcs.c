/*
** dlists_funcs.c for dlists funcs in /u/all/crevon_t/cu/rendu/lib/my/double_lists
** 
** Made by theo crevon
** Login   <crevon_t@epitech.net>
** 
** Started on  Mon Jan 11 14:12:59 2010 theo crevon
** Last update Wed Mar 17 19:11:27 2010 theo crevon
*/

#include	<stdlib.h>
#include	<dirent.h>

#include	"my.h"

int		insert_bef_xlink(t_list *list, char *data, int x)
{
  int		list_pos;
  t_link	*new_elem;
  t_link	*current;

  list_pos = 1;
  new_elem = NULL;
  new_elem = fill_link(new_elem, data);
  current = xmalloc(sizeof(*current));
  current = list->head;
  while (list_pos < x)
    {
      current = current->next;
      list_pos++;
    }
  new_elem->next = current;
  new_elem->previous = current->previous;
  if (current->previous == NULL)
    list->head = new_elem;
  else
    current->previous->next = new_elem;
  current->previous = new_elem;
  list->size++;
  return (0);
}

int		insert_after_xlink(t_list *list, char *data, int x)
{
  int		list_pos;
  t_link	*new_elem;
  t_link	*current;

  list_pos = 1;
  new_elem = NULL;
  new_elem = fill_link(new_elem, data);
  current = xmalloc(sizeof(*current));
  current = list->head;
  while (list_pos < x)
    {
      current = current->next;
      list_pos++;
    }
  new_elem->next = current->next;
  new_elem->previous = current;
  if (current->next == NULL)
    list->tail = new_elem;
  else
    current->next->previous = new_elem;
  current->next = new_elem;
  list->size++;
  return (0);
}
