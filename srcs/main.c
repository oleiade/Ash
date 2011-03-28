/*
** main.c for minishell2 in /u/all/gsell_f/cu/rendu/c/minishell2
** 
** Made by francois-xavier gsell
** Login   <gsell_f@epitech.net>
** 
** Started on  Tue Feb  9 10:41:35 2010 francois-xavier gsell
** Last update Sun May 23 11:48:06 2010 francois-xavier gsell
*/

#include	<unistd.h>
#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include	<signal.h>
#include	<fcntl.h>
#include	<stdlib.h>
#include	<dirent.h>

#include	"my.h"
#include	"42sh.h"
#include	"lexer.h"
#include	"parser.h"
#include	"conf.h"
#include	"get_next_line.h"
#include	"termc.h"
#include	"alias.h"
#include	"auto.h"
#include	"history.h"

static char	*get_buffer(t_list *histo)
{
  t_tutils	utils;

  xwrite(1, PROMPT, strlen(PROMPT));
  if (get_term() || init_termcaps(&utils))
    return (get_next_line(0));
  else
    return (termcaps(&utils, histo));
}

static void	initsh(t_lexlist **list,
		       t_list **histo,
		       t_sllist **myenv)
{
  *list = NULL;
  *histo = get_hist_from_file(HISTORY_FILE, myenv);
  if (!*histo)
    *histo = init_history();
  update_alias(1, NULL);
  load_conf(myenv);
  auto_comp(NULL, NULL, 0, *myenv);
  update_history(*histo);
}

void		mysh(int script, t_sllist **myenv)
{
  char		*buffer;
  t_list	*histo;
  t_lexlist	*list;

  initsh(&list, &histo, myenv);
  if (!script)
    disable_sig();
  while (1)
    {
      if (!script)
	buffer = get_buffer(histo);
      else
	buffer = get_next_line(0);
      list = get_lexlist(buffer);
      if (parser(list, myenv) == QUIT)
	buffer = 0;
      if (buffer == 0)
	{
	  put_hist_to_file(histo, myenv);
	  return ;
	}
    }
}

int		main(int argc, char **argv)
{
  extern char	**environ;
  t_sllist	*myenv;
  int		fd;

  build_env(environ, &myenv);
  if (argc > 1)
    {
      if (!access(argv[1], R_OK))
	{
	  fd = xopen(argv[1], O_RDONLY, 0644);
	  xdup2(fd, 0);
	  mysh(1, &myenv);
	  xclose(fd);
	}
      else
	fprintf(stderr, "%s %s\n", "Unable to access :", argv[1]);
    }
  else
    mysh(!isatty(0), &myenv);
  free_env(myenv);
  auto_comp(NULL, NULL, DEL, NULL);
  return (EXIT_SUCCESS);
}
