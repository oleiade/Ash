/*
** xunistd.c for minishell2 in /home/fxgsell/Programing/minishell
** 
** Made by francois-xavier gsell
** Login   <gsell_f@epitech.net>
** 
** Started on  Thu Mar  4 10:41:49 2010 francois-xavier gsell
** Last update Fri May 21 11:02:39 2010 demay-_l
*/

#include	<stdlib.h>
#include	<stdio.h>
#include	<errno.h>
#include	<fcntl.h>
#include	<unistd.h>
#include	<errno.h>
#include	<dirent.h>
#include	<string.h>

#include	"my.h"
#include	"42sh.h"
#include	"error_msgs.h"

int		xclose(int fd)
{
  int		ret;

  if ((ret = close(fd)) == -1)
    {
      fprintf(stderr, "Close Error: ");
      my_put_errno(errno);
      fprintf(stderr, "\n");
    }
  return (ret);
}

int		xopen(char *file, int opt, int mod)
{
  int		fd;

  fd = open(file, opt, mod);
  if (fd == -1)
    {
      fprintf(stderr, "Open Error: ");
      fprintf(stderr, "%s\n", (char *)strerror(errno));
      fprintf(stderr, "\n");
      return (-1);
    }
  return (fd);
}

int		xread(int fd, void *buf, int size)
{
  int		nb_read;

  nb_read = read(fd, buf, size);
  if (nb_read == -1 && errno != EINTR)
    {
      fprintf(stderr, "Read Error: ");
      fprintf(stderr, "%s\n", (char *)strerror(errno));
      fprintf(stderr, "\n");
    }
  return (nb_read);
}

int		xwrite(int d, const void *buf, int nbytes)
{
  if (write(d, buf, nbytes) == -1)
    {
      fprintf(stderr, "Write Error: ");
      my_put_errno(errno);
      fprintf(stderr, "\n");
      return (-1);
    }
  return (0);
}
