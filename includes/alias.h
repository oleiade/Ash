#ifndef		__ALIAS_H__
# define	__ALIAS_H__

# define	UNALIAS_ERR	"Unalias: Not enough arguments\n"
# define	UNALIAS_UNFOUND	"Unalias: No such element: "
# define	ERR_LOOP	"Alias loop :(\n"
# define	ERR_ALIAS	"Fucking error with alias comand\n"
# define	ALIAS_LOCK	30

typedef struct		s_alias
{
  char			*name;
  char			*value;
  struct s_alias	*next;
}			t_alias;

/*
** lib
*/
void		add_alias(char *name, char *value, t_alias **begin);
void		print_alias(t_alias *alias, char *the_alias);
void		list_alias(t_alias *alias);
void		check_alias(char *name, char *value, t_alias *alias);
void		del_alias(t_alias **start, t_alias *del);

/*
** Functions
*/
char		*check_if_alias(char *cmd, char *bkcmd, int f);
t_alias		*update_alias(int flag, t_alias *new_alias);
int		put_alias(t_alias *, char *, char *, int);

#endif		/*__ALIAS_H__*/
