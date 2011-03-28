/*
** error.c for minishell2 in /u/all/gsell_f/cu/rendu/c/minishell2
** 
** Made by francois-xavier gsell
** Login   <gsell_f@epitech.net>
** 
** Started on  Tue Feb  9 10:42:11 2010 francois-xavier gsell
** Last update Wed May 19 16:33:09 2010 demay-_l
*/

#include		<stdlib.h>
#include		<stdio.h>
#include		<dirent.h>

#include		"my.h"

int			my_put_errno(int nb)
{
  unsigned int		number;
  int			divisor;

  number = nb;
  divisor = 1;
  if (nb < 0)
    {
      putc('-', stdout);
      number = -nb;
    }
  while ((number / divisor) >= 10)
    divisor = divisor * 10;
  while (divisor)
    {
      putc((number / divisor) % 10 + '0', stdout);
      divisor = divisor / 10;
    }
  return (0);
}

void		puterr_exec(char *bin)
{
  fprintf(stderr, "Execve Error: %s\n", bin);
}
