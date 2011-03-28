#include	<stdlib.h>
#include	<string.h>
#include	<sys/types.h>
#include	<dirent.h>
#include	<sys/ioctl.h>
#include	<termios.h>

#include	"my.h"
#include	"42sh.h"
#include	"lexer.h"
#include	"termc.h"
#include	"auto.h"

static void	aff_space_divided(int len_b, int space, int divid, int len)
{
  while (len_b < space && divid <= len)
    {
      my_outc(' ');
      len_b++;
    }
}

static void	aff_divided(char **tab, int divid, int len, int *tab_space)
{
  int		i;
  int		i_b;
  int		j;
  int		divid_b;

  i = 0;
  i_b = 0;
  j = 0;
  divid_b = divid;
  while (divid_b > 0)
    {
      while (i <= len)
	{
	  my_outs(tab[i]);
	  aff_space_divided(strlen(tab[i]), tab_space[j], i + divid, len);
	  j++;
	  i += divid;
	}
      j = 0;
      my_outc('\n');
      i_b++;
      i = i_b;
      divid_b--;
    }
}

static int	find_most(int divid, int *space_tab, int i, int len)
{
  int		divid_b;
  int		len_buff;

  divid_b = 0;
  len_buff = 0;
  while (divid_b < divid)
    {
      if (i + divid_b <= len)
	if (len_buff < space_tab[i + divid_b])
	  len_buff = space_tab[i + divid_b];
      divid_b++;
    }
  return (len_buff);
}

static int	*find_most_len(int *space_tab, int divid, int len)
{
  int		*most_len;
  int		i;
  int		j;

  i = 0;
  j = 0;
  most_len = xmalloc((10 + len) * sizeof(*most_len));
  while (i <= len)
    {
      most_len[j] = find_most(divid, space_tab, i, len);
      j++;
      i += divid;
    }
  return (most_len);
}

void		aff_tty(char **tab, int len)
{
  int		len_total;
  int		len_total_divided;
  int		*tab_space;
  int		*most_space_tab;
  int		divid;
  t_ws		col_len;

  len_total = calc_len(tab, len);
  tab_space = calc_tab_space(tab, len);
  divid = 1;
  most_space_tab = find_most_len(tab_space, divid, len);
  len_total_divided = sum_space(most_space_tab, len / divid);
  xioctl(0, TIOCGWINSZ, &col_len);
  while (len_total_divided >= col_len.ws_col)
    {
      free(most_space_tab);
      divid++;
      most_space_tab = find_most_len(tab_space, divid, len);
      len_total_divided = sum_space(most_space_tab, len / divid);
    }
  aff_divided(tab, divid, len, most_space_tab);
  free(most_space_tab);
  free(tab_space);
  free_argv(tab);
}
