/*
** my_str_isalpha.c for my_str_isalpha in /u/all/crevon_t/svn/42sh/trunk
** 
** Made by theo crevon
** Login   <crevon_t@epitech.net>
** 
** Started on  Thu May  6 16:22:39 2010 theo crevon
** Last update Thu May  6 16:22:41 2010 theo crevon
*/

#include	<stdlib.h>
#include	<dirent.h>
#include	<string.h>

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
