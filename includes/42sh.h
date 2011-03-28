#ifndef		__42SH_H__
# define	__42SH_H__

#include	"my.h"
#include	"lexer.h"
#include	"parser.h"

# define	PROMPT			"$> "
# define	PS1			"{\\u@\\H} \\t ==>"
# define	PROMPT2			"? "
# define	ERR_UNABLE		"Command not found : "
/*
** =============== CONF AND CACHE FILES PLACES ===============
*/
# define	EXECS_LISTING_FILE	"../../conf_files/execs_listing.42conf"
# define	HISTORY_FILE_SAVE	"../../conf_files/history_backup.42save"
# define	HISTORY_FILE		".history.42sh"
# define	ERR_NOPWD		"Error : No Pwd Var found!\n"
# define	ERR_VAR			"Undefined variable."
# define	ERR_ISNOTFOLD		" : is not a folder\n"
# define	ERR_CDTOO_MANY		"Cd : Too many arguments!\n"
# define	ERR_BUILTIN_HISTORY	"Usage : history [nb_entries]\n"
# define	HELP			"42sh  Help : exit, cd,  env, setenv" \
					",  unsetenv,  help,  alias, history!\n"
# define	BG_PRC			"Background process : "
# define	ERR_HELP                "Help  :  No  options  available!\n"

/*
** =============== PS1 MACROS ===============
*/
# define        IS_HOST(c)              (c == 'H')
# define        IS_USER(c)              (c == 'u')
# define        IS_PWD(c)              (c == 'w')
# define        IS_TIME(c)              (c == 't')

/*
**  =============== STRUCTURE ===============
*/

/*
** Builtin struct that's set in order
** to call the right builtin function,
** when parser meets one.
*/

typedef struct		s_builtin
{
  char			*built_in;
  int			(*ptr_built_in)(char **, t_sllist **);
}			t_builtin;

/*
**  =============== FUNCTIONS DEFINITION ===============
*/

/*
** Builtin functions definition
*/

int		built_in(char **, t_sllist **, t_fifo_elem *);
int		built_in_help(char **, t_sllist **);
int		built_in_echo(char **, t_sllist **);
int		built_in_cd(char **, t_sllist **);
int		built_in_env(char **, t_sllist **);
int		built_in_unsetenv(char **, t_sllist **);
int		built_in_setenv(char **, t_sllist **);
int		built_in_alias(char **, t_sllist **);
int		built_in_unalias(char **, t_sllist **);
int		built_in_history(char **, t_sllist **);
int		clear_path(char *);
int		is_builtin(char *);
char		*make_new_pwd(char *, char *);
t_list		*update_history(t_list *history);

/*
** PS1 Functions
*/
t_list		*manage_tags(t_list *list, t_sllist **env, char c);
t_list		*get_env_elems(t_sllist **env, char *ps1);
char		*set_ps1(t_sllist **env);
int		main(int argc, char **argv);
char		*get_hostname(t_sllist **env);
char		*get_username(t_sllist **env);
char		*get_pwd(t_sllist **env);
char		*get_time(void);

/*
** Lists related functions definition
*/

char		**list_to_tab(t_sllist *);
int		free_list_tab(char **);
t_sllist       	*add_to_list(t_sllist **, char *, char *);
t_sllist       	*found_in_list(t_sllist *, char *);
void		alias_lexlist(t_lexlist *list);

/*
** Env related functions definition
*/

char		*my_getenv(char *, t_sllist *);
char		*mk_envname(char *);
char		*mk_envdata(char *);
int		build_env(char **, t_sllist **);
int		free_env(t_sllist *);
int		put_env(t_sllist *);
int		rm_list_elem(t_sllist *);
int		my_unsetenv(char *, t_sllist **);
int		my_setenv(char *, char *, t_sllist **);
int		strecmp(char *, char *);
char		*my_strnamecpy(char *, char *);
int		is_env_test(char *);
int		free_path(char **);
char		**path_to_tab(char *);
char		*my_abspath(t_sllist **env, char *path);

/*
** Parser related functions definition
*/

int		get_first_word(char *);
int		get_last_word(char *);
int		get_next_char(char *, int);
int		clear_line(char *);

int		set_out_redirect(char **, int, t_fifo_elem *);
int		set_in_redirect(char **, int, t_fifo_elem *);
int		set_redirect(char **, int, t_fifo_elem *);

int		set_in_red(t_fifo_elem *);
int		set_out_red(t_fifo_elem *);
int		set_pipe_red(t_fifo_elem *);
int		set_red(t_fifo_elem *);
int		setvar(t_lexlist *, t_sllist *);
int		close_red(t_fifo_elem *);

int		cmp_to_spec(char *);
char		*strdup(const char *);
int		test_coma(char **, int);
int		test_red(char **, int);
int		test_first(char **);

t_fifo		*pre_parseur(char **);
int		check_argv(char **);
int		exec_elem(t_fifo_elem *, t_sllist **);
int		exec_fifo(t_fifo *, t_sllist **);
int		parser(t_lexlist *, t_sllist **);

int		start_proc(char **, t_sllist **);

/*
** time functions
*/
#ifdef		Linux
int		usleep(int microseconds);
#endif		/* __LINUX__ */

#endif		/* __42SH_H__ */
