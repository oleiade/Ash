/*
** xfunc2.c for 42sh in /home/hugo
** 
** Made by Hugo CUVILLIER
** Login   <hugo@epitech.net>
** 
** Started on  Wed May  5 11:08:25 2010 Hugo CUVILLIER
** Last update Wed May  5 11:19:09 2010 Hugo CUVILLIER
*/

#include	<unistd.h>
#include	<dirent.h>
#include	<stdio.h>

#include	"42sh.h"

int		xpipe(int my_pipe[2])
{
  int		i;

  i = pipe(my_pipe);
  if (i == -1)
    fprintf(stderr, ERR_PIPE);
  return (i);
}
