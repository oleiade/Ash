#ifndef		__CONF_H__
# define	__CONF_H__

# define	COMMENT_CHAR	'#'
# define	CONF_NAME	".42shrc"
# define	CONF_ERR	".42shrc have been created.\n"

void		load_conf(t_sllist **myenv);
int		parse_load_line(char *buf, t_lexlist *list, t_sllist **my_env);
int		check_file(char *, char *);

#endif		/* __ALIAS_H__ */
