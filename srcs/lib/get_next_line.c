/*
** get_next_line.c for minishell2 in /u/all/gsell_f/cu/rendu/c/minishell2
** 
** Made by francois-xavier gsell
** Login   <gsell_f@epitech.net>
** 
** Started on  Tue Feb  9 10:41:50 2010 francois-xavier gsell
** Last update Thu May  6 16:33:57 2010 theo crevon
*/

#include	<stdlib.h>
#include	<string.h>
#include	<unistd.h>
#include	<dirent.h>

#include	"my.h"
#include	"42sh.h"
#include	"get_next_line.h"

char		*get_next_line(int fd)
{
  static char	buff[BUFF_SIZE];
  static int	i = 0;
  static int	nbread = 0;
  int		n;
  char		*str;

  n = 0;
  if ((read_line(fd, &i, &nbread, buff)) == 0)
    return (NULL);
  str = xmalloc(sizeof(char) * (BUFF_SIZE + 1));
  memset(str, 0, BUFF_SIZE + 1);
  while (buff[i] && buff[i] != '\n' && n < BUFF_SIZE)
    {
      str[n++] = buff[i++];
      if ((read_line(fd, &i, &nbread, buff)) == 0)
	return (str);
    }
  if (n == BUFF_SIZE)
  {
    while (buff[i] && buff[i++] != '\n')
      if (read_line(fd, &i, &nbread, buff))
	break ;
  }
  else
    i++;
  str[BUFF_SIZE] = '\0';
  return (str);
}

int		read_line(int fd, int *i, int *nbread, char *buff)
{
  if (*i == *nbread)
    {
      *i = 0;
      if ((*nbread = xread(fd, buff, BUFF_SIZE)) == 0)
	return (0);
    }
  return (1);
}
