#ifndef		__TERMC_H__
# define	__TERMC_H__

/*
** =============== KEYS DEFINITION ===============
*/
# define	BUFF_LIMIT	512
# define	KUP		65
# define	KDOWN		66
# define	KRIGHT		67
# define	KLEFT		68
# define	READ_S		10

/*
**   Associated Keys:
** "cm" ==> cursor motion
** "le" ==> left
** "nd" ==> right
** "kb" ==> backspace
** "so" ==> standout
** "se" ==> standout end
** "vi" ==> invisible cursor
** "cr" ==> carriage return
** "ve" ==> visible cursor
** "ks" ==> key enable
*/

/*
** =============== TYPES DEFINITION ===============
*/
typedef	struct	termios	t_termios;
typedef	struct	winsize	t_ws;

typedef	struct	s_com
{
  struct s_com	*prev;
  int		is_on;
  char		c;
  struct s_com	*next;
}		t_com;

typedef	struct	s_termc
{
  int		nb_char;
  int		is_ready;
  t_com		*begin;
  t_com		*end;
}		t_termc;

typedef	struct	s_tutils
{
  t_termios	*old;
  char		**termcaps;
}		t_tutils;

/*
** =============== FUNCTIONS DEFINITION ===============
*/

/*
** gestion des touches
*/
void		read_buff(char *buff);

/*
** termcaps
*/
void		init_func(t_termc *list, t_tutils *utils);
int		init_termcaps(t_tutils *utils);
char		*termcaps(t_tutils *utils, t_list *histo);
void		non_canonical_mode(t_tutils *utils);
int		restore_mode(t_tutils *utils, char *);
t_termc		*test_buff(char *buff, t_termc *li, t_tutils *ut, t_link *his);
char		*rtn_fct(char *b, t_tutils *ut, t_termc *list, t_list *hist);
char		*make_res(t_termc *list, t_list *history);
t_termc		*prepare_to_return(t_termc *list, t_tutils *ut, char *buff);
int		is_good_char(char *buff, t_tutils *ut, t_termc *list, t_ws *ws);
void		backspace_key(t_tutils *utils, t_termc *list);
t_termc		*home_end_key(char *buff, t_termc *list);

/*
** list
*/
void		empty_line(int len, t_tutils *utils);
char		*list_to_char(t_termc *list);
void		char_to_list(t_termc *list, char c);
void		del_char(t_termc *list, t_com *com);
void		aff_list(t_termc *list, t_tutils *utils);
t_com		*find_is_on(t_termc *list);
t_termc		*init_char_list(void);
t_termc		*str_to_list(char *str);
void		begin_line(t_tutils *utils);
void		add_to_char_list(t_termc *list, t_com *com, char c);
void		unselect_list(t_termc *list);
void		free_char_list(t_termc *list);

/*
** x_funcs && utils
*/
void		xioctl(int d, int request, void *l);
char		*xtgetstr(char *cap, char **area);
int		get_term(void);
int		my_outc(int c);
int		my_outs(char *c);

/*
** ctrl fct
*/
void		ctrl_c_get(void);
void		ctrl_c(void);
t_termc		*ctrl_e(char *buff, t_termc *list, t_tutils *utils);
t_termc		*ctrl_k(char *buff, t_termc *list, t_tutils *utils);
t_termc		*ctrl_a(char *buff, t_termc *list, t_tutils *utils);
t_termc		*ctrl_h(char *buff, t_termc *list, t_tutils *ut);
t_termc		*ctrl_d(char *buff, t_termc *list, t_tutils *ut);
t_termc		*ctrl_l(char *buff, t_termc *list, t_tutils *ut);
int		is_ctrl(char b);
t_termc		*test_ctrl_fct(char *buff, t_termc *list, t_tutils *ut);
void		sig_winch(void);
#endif		/* !__TERMC_H__*/
