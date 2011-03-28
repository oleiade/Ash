#include	<stdlib.h>
#include	<unistd.h>
#include	<sys/types.h>
#include	<stdio.h>
#include	<signal.h>
#include	<sys/wait.h>
#include	<string.h>
#include	<dirent.h>

#include	"42sh.h"
/*
** - Manages the exit value of the last process.
** - Displays the str corresponding on the value.
*/

static void	manage_status(t_fifo_elem *cur, int status)
{
  if (WTERMSIG(status))
    printf("Process %s %s !\n",
	   cur->data.argv[0],
	   my_strsignal(WTERMSIG(status)));
  cur->data.return_val = WEXITSTATUS(status);
  if (cur->up != NULL && cur->next == NULL)
    cur->up->data.return_val = cur->data.return_val;
}

/*
** - Manages the redirection by dupping the stdin || stdou ||
**   stderr in a fd stored on elem.
*/

static int	manage_child(t_fifo_elem *cur, t_sllist **myenv)
{
  if (cur->data.fd[IN])
    xdup2(cur->data.fd[IN], 0);
  if (cur->data.fd[OUT])
    xdup2(cur->data.fd[OUT], 1);
  if (cur->data.flag[ERR])
    xdup2(cur->data.fd[OUT], 2);
  execute_extern(cur->data.argv, myenv);
  return (EXIT_SUCCESS);
}

static int	manage_fork(t_fifo_elem *cur, t_sllist **myenv, int *status)
{
  cur->data.pid = xfork();
  if (!cur->data.pid)
    return (manage_child(cur, myenv));
  if (cur->data.flag[DSYNC])
    {
      printf("%s%d\n", BG_PRC, cur->data.pid);
      usleep(150);
    }
  else if (cur->data.pid > 0 &&
	   (!F_ISPIPE(cur->data.flag[OUT]) ||
	    !cur->next))
    {
      xwaitpid(cur->data.pid, status, 0);
      manage_status(cur, *status);
    }
  return (EXIT_SUCCESS);
}

/*
** - Fork to execute.
** - Set input/output redirection before execution.
** - Execute command.
*/
int		manage_execution(t_fifo_elem *cur, t_sllist **myenv)
{
  int		status;

  status = 0;
  if (cur->data.argv != NULL)
    if (cur->data.argv[0])
      {
	if (is_builtin(cur->data.argv[0]))
	  {
	    cur->data.return_val = execute_builtin(cur, myenv);
	    return (cur->data.return_val);
	  }
	else
	  if (manage_fork(cur, myenv, &status) == QUIT)
	    return (QUIT);
	return (EXIT_SUCCESS);
      }
  return (EXIT_FAILURE);
}
