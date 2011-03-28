#ifndef			PATH_H
# define		PATH_H

/*
** =============== FUNCTIONS DEFINITIONS ===============
*/
/*
** PATH management functions.
*/
t_sllist       		**put_path_in_list(t_sllist **env);
t_sllist       		**pathdirs_to_list(char *path_str);
t_sllist		**put_execs_in_list(t_sllist **env);
char    		*format_exec_name(char *foldername, char *filename);

#endif			/* PATH_H */
