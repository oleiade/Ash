#include	<stdio.h>
#include	<string.h>
#include	<stdlib.h>
#include	<termios.h>
#include	<sys/ioctl.h>
#include	<dirent.h>
#include	<fcntl.h>
#include	<term.h>

#ifndef		FreeBSD
/*
** # include	<stropts.h>
*/
# define	TIOCGETA TCGETS
# define	TIOCSETA TCSETS
#endif          /* !FreeBSD */

#include	"my.h"
#include	"lexer.h"
#include	"termc.h"
#include	"error_msgs.h"

/*
** - Function that initiate char list
*/
t_termc		*init_char_list()
{
  t_termc	*list;

  list = xmalloc(sizeof(*list));
  list->begin = NULL;
  list->end = NULL;
  list->is_ready = 0;
  return (list);
}

/*
** - First init func, for termcaps use and make struct/lists
*/
void		init_func(t_termc *list, t_tutils *utils)
{
  tputs(utils->termcaps[6], 1, my_outc);
  tputs(utils->termcaps[9], 1, my_outc);
  non_canonical_mode(utils);
  aff_list(list, utils);
}

/*
** - Explicit Func
*/
void		xioctl(int d, int request, void *l)
{
  if (request == TIOCGWINSZ)
    l = (t_ws *)l;
  else
    l = (t_termios *)l;
  if (ioctl(d, request, l) < 0)
  {
    fprintf(stderr, IOCTL_ERR);
    exit(EXIT_FAILURE);
  }
}

/*
** - Put char to current tty
*/
int		my_outc(int c)
{
  static int	tty;

  if (!tty)
    tty = xopen("/dev/tty", O_WRONLY, 0);
  xwrite(tty, &c, 1);
  return (0);
}

/*
** - Put string to current tty
*/
int		my_outs(char *c)
{
  static int	tty;

  if (!tty)
    tty = xopen("/dev/tty", O_WRONLY, 0);
  xwrite(tty, c, strlen(c));
  return (0);
}
