/*
** str.c for minishell2 in /u/all/gsell_f/cu/rendu/c/minishell2
** 
** Made by francois-xavier gsell
** Login   <gsell_f@epitech.net>
** 
** Started on  Tue Feb  9 10:40:54 2010 francois-xavier gsell
** Last update Wed May 19 17:16:59 2010 hugo cuvillier
*/

#include	<dirent.h>
#include	<string.h>

#include	"my.h"

void		my_putstr(char *c)
{
  xwrite(1, c, strlen(c));
}
