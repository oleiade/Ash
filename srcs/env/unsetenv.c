#include	<stdio.h>
#include	<unistd.h>
#include	<stdlib.h>
#include	<string.h>
#include	<dirent.h>

#include	"my.h"
#include	"42sh.h"

int		built_in_unsetenv(char **argv, t_sllist **myenv)
{
  if (argv[1] != 0 && argv[2] == 0)
    my_unsetenv(argv[1], myenv);
  else
    fprintf(stderr, "Usage : unsetenv VAR\n");
  return (0);
}

int		rm_list_elem(t_sllist *myenv)
{
  free(myenv->data);
  free(myenv->name);
  free(myenv);
  return (0);
}

int		my_unsetenv(char *name, t_sllist **myenv)
{
  t_sllist	*tmp;
  t_sllist	*prev;

  tmp = *myenv;
  if (*myenv != 0)
    if (strcmp((*myenv)->name, name) == 0)
      {
	prev = (*myenv)->next;
	rm_list_elem(*myenv);
	*myenv = prev;
	return (0);
      }
  while (tmp->next != NULL)
    {
      if (strcmp(tmp->next->name, name) == 0)
	{
	  prev = tmp->next->next;
	  rm_list_elem(tmp->next);
	  tmp->next = prev;
	  return (0);
	}
      tmp = tmp->next;
    }
  return (0);
}
