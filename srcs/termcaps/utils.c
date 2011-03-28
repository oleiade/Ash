#include	<stdlib.h>
#include	<stdio.h>
#include	<sys/ioctl.h>
#include	<termios.h>
#include	<unistd.h>
#include	<sys/types.h>
#include	<dirent.h>
#include	<term.h>

#ifndef		FreeBSD
# define	TIOCGETA	TCGETS
# define	TIOCSETA	TCSETS
#else
# include	<termcap.h>
#endif		/* !FreeBSD */

#include	"42sh.h"
#include	"my.h"
#include	"lexer.h"
#include	"termc.h"

/*
** - Test if term exist for Termcaps
*/
int		get_term()
{
  char		*term;
  char		bp[1024];

  if ((term = getenv("TERM")) == NULL)
    return (1);
  if (tgetent(bp, term) != 1)
    return (1);
  return (0);
}

/*
** - Function that prepare termcaps
** - and make cursor invisible
*/
int		init_termcaps(t_tutils *utils)
{
  int		i;
  char		*area;

  area = NULL;
  utils->termcaps = xmalloc(12 * sizeof(*(utils->termcaps)));
  utils->termcaps[0] = tgetstr("cm", &area);
  utils->termcaps[1] = tgetstr("le", &area);
  utils->termcaps[2] = tgetstr("nd", &area);
  utils->termcaps[3] = tgetstr("kb", &area);
  utils->termcaps[4] = tgetstr("so", &area);
  utils->termcaps[5] = tgetstr("se", &area);
  utils->termcaps[6] = tgetstr("vi", &area);
  utils->termcaps[7] = tgetstr("cr", &area);
  utils->termcaps[8] = tgetstr("ve", &area);
  utils->termcaps[9] = tgetstr("ks", &area);
  utils->termcaps[10] = tgetstr("cl", &area);
  utils->termcaps[11] = NULL;
  i = 0;
  while (i <= 10)
  {
    if (utils->termcaps[i] == NULL)
      return (1);
    i++;
  }
  return (0);
}

/*
** - Put term in non canonical mode
*/
void		non_canonical_mode(t_tutils *utils)
{
  t_termios	line;

  utils->old = xmalloc(sizeof(*(utils->old)));
  if (tcgetattr(0, &line) < 0)
    printf("tcgetattr");
  *utils->old = line;
  line.c_lflag &= ~(ICANON | ECHO | ISIG);
  line.c_cc[VMIN] = 1;
  line.c_cc[VTIME] = 0;
  if (tcsetattr(0, TCSANOW, &line) < 0)
    printf("tcsetattr");
}

/*
** - Function that restore term from original value,
*/
int		restore_mode(t_tutils *utils, char *tmp)
{
  tputs(utils->termcaps[8], 1, my_outc);
  if (tcsetattr(0, TCSANOW, utils->old) < 0)
    my_outs("tcsetattr");
  free(utils->old);
  if (tmp != NULL)
    free(tmp);
  return (0);
}
