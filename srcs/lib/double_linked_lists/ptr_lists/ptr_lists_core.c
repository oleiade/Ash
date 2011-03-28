/*
** ptr_lists_core.c for 42sh in /u/all/gsell_f/cu/rendu/c/proj/42sh/trunk
** 
** Made by francois-xavier gsell
** Login   <gsell_f@epitech.net>
** 
** Started on  Fri Apr 16 15:23:15 2010 francois-xavier gsell
** Last update Fri May  7 12:42:00 2010 theo crevon
*/

#include <stdlib.h>
#include <dirent.h>

#include "my.h"

t_ptrlist	*init_ptrlist(t_ptrlist *ptrlist)
{
  ptrlist = xmalloc(sizeof(t_ptrlist));
  ptrlist->pos = 1;
  ptrlist->data_ptr = NULL;
  ptrlist->previous_ptr = NULL;
  return (ptrlist);
}

t_ptrlist		*add_to_ptrlist(t_ptrlist *ptrl, char *data, int pos)
{
  t_ptrlist		*new_ptr;

  new_ptr = xmalloc(sizeof(*new_ptr));
  if (ptrl->previous_ptr == NULL && ptrl->data_ptr == NULL)
    {
      ptrl->pos = pos;
      ptrl->data_ptr = data;
      ptrl->previous_ptr = NULL;
      return (ptrl);
    }
  else
    {
      new_ptr->pos = pos;
      new_ptr->data_ptr = data;
      new_ptr->previous_ptr = ptrl;
    }
  return (new_ptr);
}
