/*
** dlists_core.c for dlists core in /u/all/crevon_t/cu/rendu/lib/my/double_lists
** 
** Made by theo crevon
** Login   <crevon_t@epitech.net>
** 
** Started on  Mon Jan 11 13:39:12 2010 theo crevon
** Last update Sun May 23 16:55:25 2010 florian greiner
*/

#include	<stdlib.h>
#include	<string.h>
#include	<dirent.h>

#include	"42sh.h"
#include	"my.h"

t_link		*fill_link(t_link *link, char *data)
{
  link = xmalloc(sizeof(*link));
  if (data != NULL)
    link->data = strdup(data);
  return (link);
}

void		init_list(t_list *list)
{
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
}

int		insert_first_link(t_list *list, char *data)
{
  t_link	*new_elem;

  new_elem = NULL;
  new_elem = fill_link(new_elem, data);
  new_elem->next = list->tail;
  new_elem->previous = list->head;
  list->tail = new_elem;
  list->head = new_elem;
  list->size++;
  return (0);
}

int		insert_beginning(t_list *list, char *data)
{
  t_link	*new_elem;

  new_elem = NULL;
  if (list->head == NULL)
    return (insert_first_link(list, data));
  new_elem = fill_link(new_elem, data);
  new_elem->previous = NULL;
  new_elem->next = list->head;
  list->head->previous = new_elem;
  list->head = new_elem;
  list->size++;
  return (0);
}

int		insert_end(t_list *list, char *data)
{
  t_link	*new_elem;

  new_elem = NULL;
  if (list->tail == NULL)
    return (insert_first_link(list, data));
  new_elem = fill_link(new_elem, data);
  new_elem->next = NULL;
  new_elem->previous = list->tail;
  list->tail->next = new_elem;
  list->tail = new_elem;
  list->size++;
  return (0);
}
