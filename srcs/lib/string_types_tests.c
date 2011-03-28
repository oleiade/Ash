/*
** string_types_tests.c for string_types_tests in /u/all/crevon_t/svn/42sh/trunk
** 
** Made by theo crevon
** Login   <crevon_t@epitech.net>
** 
** Started on  Thu May  6 16:23:27 2010 theo crevon
** Last update Sat May 22 14:28:37 2010 hugo cuvillier
*/

#include	<stdlib.h>
#include	<dirent.h>
#include	<string.h>
#include	<ctype.h>
#include	<unistd.h>

#include	"my.h"
#include	"42sh.h"

int		my_str_isalpha(char *str)
{
  int		pos;

  pos = 0;
  while (str[pos] != '\0')
    {
      if (isalpha(str[pos]))
	pos++;
      else
	return (0);
    }
  return (1);
}

int		is_printable(char *str)
{
  int		pos;

  pos = 0;
  while (str[pos] != '\0')
    {
      if (IS_PRINTABLE(str[pos]))
	pos++;
      else
	return (0);
    }
  return (1);
}

char		*remove_ex_char(char *str, int pos)
{
  char		*new_str;
  int		in_pos;

  in_pos = 0;
  new_str = xmalloc((strlen(str) - 1) * sizeof(*new_str));
  if (pos == 0)
    new_str = strcpy(new_str, &str[1]);
  else if (pos == -1)
    {
      while (in_pos < (int)(strlen(str) - 1))
	{
	  new_str[in_pos] = str[in_pos];
	  in_pos++;
	}
    }
  return (new_str);
}
