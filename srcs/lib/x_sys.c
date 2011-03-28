/*
** x_sys.c for x_sys in /u/all/crevon_t/cu/rendu/c/minitalk/lib/xfuncs
** 
** Made by theo crevon
** Login   <crevon_t@epitech.net>
** 
** Started on  Wed Mar 17 18:40:14 2010 theo crevon
** Last update Fri May 21 11:07:19 2010 demay-_l
*/

#include	<unistd.h>
#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include	<sys/types.h>
#include	<dirent.h>
#include	<signal.h>
#include	<errno.h>

#include	"my.h"
#include	"error_msgs.h"

#ifdef		__linux__
int		readdir_r(DIR *dirp, struct dirent *entry, struct dirent **res);
int		kill(pid_t pid, int sig);
#endif

void		xclosedir(DIR *dir)
{
  if (dir != NULL)
    if (closedir(dir))
      fprintf(stderr, "closeedir");
}

int		xreaddir_r(DIR *odir, struct dirent *entry, struct dirent **res)
{
  int		result;

  result = readdir_r(odir, entry, res);
  if (result)
    {
      fprintf(stderr, "%s\n", (char *)strerror(errno));
      return (-1);
    }
  return (result);
}

struct dirent	*xreaddir(DIR *odir)
{
  struct dirent	*dp;

  dp = readdir(odir);
  if (dp == NULL)
    {
      fprintf(stderr, "%s\n", (char *)strerror(errno));
      return (NULL);
    }
  else
    return (dp);
}

DIR		*xopendir(char *name)
{
  DIR		*odir;

  if (name == NULL)
    {
      fprintf(stderr, "the name of the requested folder is empty\n");
      return (NULL);
    }
  odir = opendir(name);
  if (odir == NULL)
    {
      fprintf(stderr, "%s\n", (char *)strerror(errno));
      return (NULL);
    }
  else
    return (odir);
}

void		xkill(unsigned int pid, int sig_num)
{
  int		state;

  state = kill(pid, sig_num);
  if (state == -1)
    fprintf(stderr, KILL_ERR);
}
