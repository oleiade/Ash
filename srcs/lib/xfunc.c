/*
** xfunc.c for minishell2 in /u/all/gsell_f/cu/rendu/c/minishell2
** 
** Made by francois-xavier gsell
** Login   <gsell_f@epitech.net>
** 
** Started on  Tue Feb  9 10:40:31 2010 francois-xavier gsell
** Last update Sat May 22 12:27:12 2010 francois-xavier gsell
*/

#include	<sys/types.h>
#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include	<errno.h>
#include	<sys/wait.h>
#include	<unistd.h>
#include	<dirent.h>

#include	"my.h"
#include	"42sh.h"

int		xexecve(char **argv, char **myenv, char *path)
{
  if (path)
    {
      if (!access(path, X_OK))
	{
	  if (execve(path, argv, myenv))
	    puterr_exec(path);
	  return (1);
	}
      else
	fprintf(stderr, "%s%s!\n", ERR_UNABLE, argv[0]);
    }
  else
    fprintf(stderr, "%s%s!\n", ERR_UNABLE, argv[0]);
  return (0);
}

void		*xmalloc(unsigned int size)
{
  void		*space;

  space = malloc(size);
  if (space == 0)
    {
      fprintf(stderr, "Malloc Error:");
      my_put_errno(errno);
      fprintf(stderr, "\n");
      exit(EXIT_FAILURE);
    }
  memset(space, 0, size);
  return (space);
}

int		xwaitpid(unsigned int pid, int *status, int opts)
{
  if (waitpid(pid, status, opts) == -1)
    {
      fprintf(stderr, "Wait Error: %d\n", errno);
      return (-1);
    }
  return (0);
}

int		xfork()
{
  pid_t		pid;

  if ((pid = fork()) < 0)
    {
      fprintf(stderr, "Fork Error\n");
      my_put_errno(errno);
      fprintf(stderr, "\n");
      exit(EXIT_FAILURE);
    }
  return (pid);
}

int		xdup2(int oldd, int newd)
{
  int		ret;

  if (newd != oldd)
    xclose(newd);
  if ((ret = dup2(oldd, newd)) == -1)
    {
      fprintf(stderr, "Dup2 Error\n");
      my_put_errno(errno);
      fprintf(stderr, "\n");
      exit(EXIT_FAILURE);
    }
  return (ret);
}
