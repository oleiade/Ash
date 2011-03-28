#ifndef		__PARSER_H__
# define	__PARSER_H__

/*
** =============== MACROS DEFINITION ===============
*/

# define	F_SIOUT			(1 << 2)
# define	F_DBOUT			(1 << 1)
# define	F_PIPE			(1 << 0)

# define	F_SIIN			(1 << 1)
# define	F_DBIN			(1 << 0)

# define	F_SECOK			(1 << 2)
# define	F_SECERR		(1 << 1)
# define	F_SEC			(1 << 0)

# define	DSYNC			4
# define	ERR			3
# define	SEC			2
# define	OUT			1
# define	IN			0

# define	F_ISSIOUT(o)		(((o) & (F_SIOUT)) == (F_SIOUT))
# define	F_ISSIIN(o)		(((o) & (F_SIIN)) == (F_SIIN))
# define	F_ISPIPE(o)		(((o) & (F_PIPE)) == (F_PIPE))

# define	F_ISDBOUT(o)		(((o) & (F_DBOUT)) == (F_DBOUT))
# define	F_ISDBIN(o)		(((o) & (F_DBIN)) == (F_DBIN))

# define	F_ISSECOK(o)		(((o) & (F_SECOK)) == (F_SECOK))
# define	F_ISSECERR(o)		(((o) & (F_SECERR)) == (F_SECERR))
# define	F_ISSEC(o)		(((o) & (F_SEC)) == (F_SEC))

# define       	ERR_DELIM		"Ambiguous delimitor !\n"
# define       	ERR_INPUT_RED		"Ambiguous input redirection !\n"
# define       	ERR_OUTPUT_RED		"Ambiguous output redirection !\n"
# define       	ERR_MISSING_REDIR_NAME	"Missing name behind redirection !\n"
# define	ERR_UNMAPAR		"Error: Unmatched parenthesis!\n"
# define	ERR_BADPAR		"Error: Parenthesis badly placed!\n"
# define	EXIT_NOTHING		-2
# define	QUIT			42
# define	NEXT			1
# define	SUB			0
# define	NO_ADD			-42
/*
** =============== STRUCTURE ===============
*/

typedef struct		s_arg
{
  int			flag[5];
  int			fd[2];
  int			return_val;
  char			*file_name[2];
  char			**argv;
  unsigned int		pid;
}			t_arg;

typedef struct		s_fifo_elem
{
  t_arg			data;
  struct s_fifo_elem	*prev;
  struct s_fifo_elem	*next;
  struct s_fifo_elem	*up;
  struct s_fifo_elem	*down;
}			t_fifo_elem;

typedef struct		s_fifo
{
  struct s_fifo_elem	*end;
  struct s_fifo_elem	*begin;
  struct s_fifo_elem	*cur;
}			t_fifo;

/* Fifo*/
void		free_fifo(t_fifo *);
int		create_fifo(t_fifo *, t_lexelem **, int);
void		set_argv(t_fifo_elem *, t_lexelem *);
int		set_redir(t_fifo_elem *, t_lexelem *);
int		set_stpt(t_lexelem **);

/* Verif list*/
int		verif_list(t_lexelem *);
int		verif_par(t_lexelem *);
/* Redirections */
int		open_fd(t_fifo_elem *);
void		close_fd(t_fifo_elem *);
void		writeinpipe(char *, int);

/* Execution */
int		manage_delim(t_fifo_elem *);
int		manage_execution(t_fifo_elem *, t_sllist **);
int		execute_builtin(t_fifo_elem *, t_sllist **);
int		execute_command(t_fifo_elem *, t_sllist **);
int		launch_commands(t_fifo_elem *, t_sllist **);
int	    	execute_extern(char **argv, t_sllist **myenv);

/* Set Flags */
int		set_redir_flag(t_fifo_elem *, t_lexelem *);
void		set_delim_flag(t_fifo_elem *, t_lexelem *);

#endif
