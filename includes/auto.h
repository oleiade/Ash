#ifndef		__AUTO_H__
# define	__AUTO_H__

# define 	CTRL(x)		(x&037)
# define       	CA		CTRL('a')
# define       	CB		CTRL('b')
# define 	CINTR		CTRL('c')
# define       	CEOF		CTRL('d')
# define 	CE		CTRL('e')
# define 	CF		CTRL('f')
# define       	CG		CTRL('g')
# define       	CBS		CTRL('h')
# define       	CI		CTRL('i')
# define       	CK		CTRL('k')
# define       	CNL		CTRL('l')
# define       	CM		CTRL('m')
# define       	CN		CTRL('n')
# define 	CDISCARD	CTRL('o')
# define 	CP		CTRL('p')
# define 	CSTART		CTRL('q')
# define 	CKILL		CTRL('u')
# define 	CREPRINT	CTRL('r')
# define 	CSTOP		CTRL('s')
# define 	CT		CTRL('t')
# define 	CLNEXT		CTRL('v')
# define 	CWERASE		CTRL('w')
# define 	CX		CTRL('x')
# define 	CDSUSP		CTRL('y')
# define 	CSUSP		CTRL('z')
# define	DEL		-99
# define	MAX_CAP1	"[42sh] Do you wish to see all "
# define	MAX_CAP2	"possibilities ? [Y/n]"

typedef		struct dirent	t_dir;
struct		s_ctrl
{
  char		letter;
  char		value;
  t_termc       *(*ptr)(char *buff, t_termc *list, t_tutils *ut);
};

void		sort_list(t_list *list, t_list *path);

/*
** - Aff Funcs
*/
void		aff_tty(char **tabl, int len);
char		**list_to_double_tab(t_list *list);
int		calc_len(char **tabl, int i);
int		*calc_tab_space(char **tabl, int len);
int		sum_space(int *tabl, int len);

/*
** - Parser Funcs
*/
t_list		*parse_ex(t_list *path);
t_list		*select_exec(t_list *binary, char *str);
t_list		*parse_path(t_termc *command);
t_termc		*my_listcat(t_termc *com, t_list *list);

/*
** - Completion Funcs
*/
t_termc		*auto_comp(t_termc *, t_tutils *, int , t_sllist *);
t_termc		*manage_path(t_termc *command, t_tutils *utils, t_list *path);
void		extract_utils(t_list *list);
void		echo_completion(t_termc *com, t_tutils *utils, t_list *comp);
t_termc		*manage_auto(t_list *new_, t_termc *command, t_tutils *utils);
void		check_semi_complet(t_termc *com, t_list *list);
void		check_if_space(t_link *buff);
int		is_space(char *str);
char		*add_quote(t_link *buff);

#endif		/* __AUTO_H__ */
