/*
** my_str_to_wordlist.c for 42sh in /u/all/gsell_f/cu/rendu/c/proj/42sh/trunk
** 
** Made by francois-xavier gsell
** Login   <gsell_f@epitech.net>
** 
** Started on  Thu Apr 15 14:53:21 2010 francois-xavier gsell
** Last update Thu May 20 11:41:25 2010 francois-xavier gsell
*/

#include	<stdlib.h>
#include	<dirent.h>

#include	"my.h"
#include	"error_msgs.h"

char		*return_word(char *str, int pos_ptr, char delim1, char delim2)
{
  int		i;
  int		n;
  char		*tab;

  n = 0;
  i = pos_ptr;
  while (str[i] && (str[i] != delim1 && str[i] != delim2))
    {
      n = n + 1;
      i = i + 1;
    }
  tab = xmalloc((n + 1) * sizeof(*tab));
  n = 0;
  i = pos_ptr;
  while (str[i] && (str[i] != delim1 && str[i] != delim2))
    {
      tab[n] = str[i];
      n = n + 1;
      i = i + 1;
    }
  tab[n] = '\0';
  return (tab);
}

int		nb_word_delim(char *str, char delim)
{
  int		size;
  int		i;

  size = 0;
  i = 0;
  while (str[i] != '\0')
  {
    while (str[i] == delim || str[i] == '\t')
      i++;
    if (str[i] != '\0')
    {
      size++;
      while (str[i] != '\0' && str[i] != delim && str[i] != '\t')
	i++;
    }
    while (str[i] == delim || str[i] == '\t')
      i++;
  }
  return (size + 1);
}

t_list		*my_wordlist(char *src, char delim1, char delim2)
{
  int		i;
  int		c_word;
  t_list	*list;

  i = 1;
  c_word = nb_word_delim(src, delim1);
  list = xmalloc(sizeof(t_list));
  init_list(list);
  insert_end(list, return_word(src, 0, delim1, delim2));
  while (src[i] != '\0')
    {
      while ((src[i] != delim1) && (src[i] != delim2) && src[i] != '\0')
	i++;
      if (src[i] == delim1 && src[i + 1])
	{
	  insert_end(list, return_word(src, i + 1, delim1, delim2));
	  i++;
	}
    }
  return (list);
}
