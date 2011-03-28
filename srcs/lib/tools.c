/*
** tools.c for minishell2 in /u/all/gsell_f/cu/rendu/c/minishell2
** 
** Made by francois-xavier gsell
** Login   <gsell_f@epitech.net>
** 
** Started on  Tue Feb  9 10:40:43 2010 francois-xavier gsell
** Last update Sun May 23 16:03:36 2010 louis demay-drouhard
*/

#include	<stdlib.h>
#include	<stdio.h>
#include	<dirent.h>
#include	<unistd.h>

#include	"my.h"
#include	"42sh.h"

int		free_argv(char **argv)
{
  int		i;

  i = 0;
  if (argv != NULL)
    {
      while (argv[i] != 0)
	{
	  free(argv[i]);
	  i++;
	}
      free(argv[i]);
      free(argv);
    }
  return (0);
}
