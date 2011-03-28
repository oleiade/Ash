/*
** sig.c for minishell2 in /u/all/gsell_f/cu/rendu/c/minishell2
** 
** Made by francois-xavier gsell
** Login   <gsell_f@epitech.net>
** 
** Started on  Tue Feb  9 10:41:10 2010 francois-xavier gsell
** Last update Sun May 23 11:43:14 2010 francois-xavier gsell
*/

#include	<signal.h>
#include	<stdio.h>
#include	<dirent.h>
#include	<unistd.h>

#include	"my.h"
#include	"42sh.h"

void		disable_sig(void)
{
  if (signal(SIGINT, SIG_IGN) == SIG_ERR)
    fprintf(stderr, "SIGINT Error\n");
  if (signal(SIGTSTP, SIG_IGN) == SIG_ERR)
    fprintf(stderr, "SIGSTP Error\n");
}

void		enable_sig(void)
{
  if (signal(SIGINT, SIG_DFL) == SIG_ERR)
    fprintf(stderr, "SIGINT Error\n");
  if (signal(SIGTSTP, SIG_DFL) == SIG_ERR)
    fprintf(stderr, "SIGSTP Error\n");
}

char		*my_strsignal(int sig)
{
  char		**signals;

  if (!((sig > 0 && sig <= 20) && (sig != 5 && sig != 16 && sig != 18)))
    return ("Unknown signal");
  signals = xmalloc(sizeof(*signals) * 32);
  signals[1] = "SIGHUP : Hangup detected on controlling terminal or \
death of controlling process";
  signals[2] = "SIGINT : Interrupt from keyboard";
  signals[3] = "SIGQUIT : Quit from keyboard";
  signals[4] = "SIGILL : Illegal Instruction";
  signals[6] = "SIGABRT : Abort signal from abort(3)";
  signals[7] = "SIGBUS : Bus error";
  signals[8] = "SIGFPE : Floating point exception";
  signals[9] = "SIGKILL : Kill signal";
  signals[10] = "SIGUSR1 : User-defined signal 1";
  signals[11] = "SIGSEGV : Invalid memory reference";
  signals[12] = "SIGUSR2 : User-defined signal 2";
  signals[13] = "SIGPIPE : Broken pipe: write to pipe with no readers";
  signals[14] = "SIGALRM : ";
  signals[15] = "SIGTERM : Termination signal";
  signals[17] = "SIGCHLD : Child stopped or terminated";
  signals[19] = "SIGSTOP : Stop process";
  signals[20] = "SIGTSTP : Stop typed at tty";
  return (signals[sig]);
}

