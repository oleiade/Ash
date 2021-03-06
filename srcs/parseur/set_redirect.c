#include	<stdlib.h>
#include	<stdio.h>
#include	<dirent.h>
#include	<fcntl.h>
#include	<unistd.h>

#include	"42sh.h"
#include	"lexer.h"

static void	set_input_redirect(t_fifo_elem *cur)
{
  int		pipe[2];

  if (F_ISSIIN(cur->data.flag[IN]))
    cur->data.fd[IN] = xopen(cur->data.file_name[IN], O_RDONLY, 0644);
  else if (F_ISDBIN(cur->data.flag[IN]))
    {
      xpipe(pipe);
      writeinpipe(cur->data.file_name[IN], pipe[1]);
      cur->data.fd[IN] = pipe[0];
    }
}

static void	set_pipe(t_fifo_elem *cur, int *pipe)
{
  t_fifo_elem	*tmp;

  xpipe(pipe);
  cur->data.fd[OUT] = pipe[1];
  if (cur->next != NULL)
    {
      cur->next->data.fd[IN] = pipe[0];
      tmp = cur->next;
      while (tmp->down != NULL)
	tmp = tmp->down;
      if (tmp != NULL && tmp != cur->next)
	tmp->data.fd[IN] = pipe[0];
    }
  if (cur->down != NULL)
    {
      tmp = cur->down;
      while (tmp->next != NULL)
	tmp = tmp->next;
      tmp->data.fd[OUT] = pipe[1];
    }
}

static void	set_output_redirect(t_fifo_elem *cur)
{
  int		pipe[2];

  if (F_ISPIPE(cur->data.flag[OUT]) && !cur->data.fd[OUT])
    set_pipe(cur, pipe);
  else if (F_ISSIOUT(cur->data.flag[OUT]))
    cur->data.fd[OUT] = xopen(cur->data.file_name[OUT],
                              (O_RDWR | O_CREAT | O_TRUNC), 0644);
  else if (F_ISDBOUT(cur->data.flag[OUT]))
    cur->data.fd[OUT] = xopen(cur->data.file_name[OUT],
                              (O_RDWR | O_CREAT | O_APPEND), 0644);
}

int		open_fd(t_fifo_elem *cur)
{
  if (F_ISSIIN(cur->data.flag[IN]) ||
      F_ISDBIN(cur->data.flag[IN]))
    set_input_redirect(cur);
  if (F_ISSIOUT(cur->data.flag[OUT]) ||
      F_ISDBOUT(cur->data.flag[OUT]) ||
      F_ISPIPE(cur->data.flag[OUT]))
    set_output_redirect(cur);
  if (cur->data.fd[IN] == -1 || cur->data.fd[OUT] == -1)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

void		close_fd(t_fifo_elem *cur)
{
  if (cur->data.fd[IN] > 2)
    xclose(cur->data.fd[IN]);
  if (cur->data.fd[OUT] > 2)
    xclose(cur->data.fd[OUT]);
}
