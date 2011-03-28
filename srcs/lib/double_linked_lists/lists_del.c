/*
** dlists_del.c for dlists_del in /u/all/crevon_t/cu/rendu/c/minitalk/lib/double_lists
** 
** Made by theo crevon
** Login   <crevon_t@epitech.net>
** 
** Started on  Wed Mar 17 19:05:17 2010 theo crevon
** Last update Sun May 23 16:55:24 2010 florian greiner
*/

#include	<stdlib.h>
#include	<dirent.h>

#include	"my.h"

static void	del_first_link(t_list *list, t_link *del_elem)
{
  del_elem = list->head;
  list->head = list->head->next;
  if (list->head == NULL)
    list->tail = NULL;
  else
    list->head->previous = NULL;
}

static void	del_last_link(t_list *list, t_link *del_elem)
{
  del_elem = list->tail;
  list->tail->previous->next = NULL;
  list->tail = list->tail->previous;
}

static void	go_to_link(t_link *current, int *in_pos, int *pos)
{
  while (*in_pos < *pos)
    {
      current = current->next;
      (*in_pos)++;
    }
}

int		del_dlist_id(t_list *list, int pos)
{
  int		in_pos;
  t_link	*del_elem;
  t_link	*current;

  del_elem = NULL;
  in_pos = 0;
  if (list->size == 0)
    return (-1);
  if (pos == 1)
    del_first_link(list, del_elem);
  else if (pos == list->size)
    del_last_link(list, del_elem);
  else
    {
      current = list->head;
      go_to_link(current, &in_pos, &pos);
      del_elem = current;
      current->previous->next = current->next;
      current->next->previous = current->previous;
    }
  free(del_elem);
  list->size--;
  return (0);
}

void		freemylist(t_list *list)
{
  t_link	*cur;
  t_link	*todel;

  if (list != NULL)
  {
    cur = list->head;
    while (cur != NULL)
      {
	todel = cur;
	cur = cur->next;
	free(todel->data);
	free(todel);
      }
    free(list);
  }
}
