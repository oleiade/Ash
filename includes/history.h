#ifndef		__HISTORY_H__
# define	__HISTORY_H__

/*
** =============== MACROS DEFINTIONS ================
*/
# define	PREV_LINK	1
# define	NEXT_LINK	2

/*
** =============== FUNCTIONS DEFINTIONS ================
*/
t_list		*init_history(void);
t_list		*add_stdin_to_history(char *str, t_list *history);
char		*get_history_link(t_link *current_link, int );
void		put_hist_to_file(t_list *history, t_sllist **myenv);
t_list		*get_hist_from_file(char *filename, t_sllist **myenv);
char		*concat_filename(char *filename, char *home);

#endif		/* HISTORY_H */
