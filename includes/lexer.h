#ifndef		LEXER_H
# define	LEXER_H

/*
** =============== MACROS ===============
*/

/*
** Keep in mind that 34 = " ; 39 = ' ; 96 = `
*/
# define	IS_PAR(a)      	(a == '(' || a == ')')
# define	IS_PIPE(a)     	(a == '|')
# define	IS_OPENPAR(a)  	(a == '(')
# define	IS_CLOSEPAR(a) 	(a == ')')
# define	IS_BQUOTE(a)   	(a == 96)
# define	IS_QUOTE(a)    	(a == 39)
# define	IS_DQUOTE(a)   	(a == 34)
# define	IS_AND(a)	(a == '&')

# define	ERR_UNMAQUO	"Error: Unmatched quote!\n"

/*
** =============== STRUCTURES DEFINITIONS ===============
*/

typedef struct		s_sllist
{
  struct s_sllist	*next;
  char			*name;
  char			*data;
}			t_sllist;

/*
** Enum to set different kinds of lexical elements
*/
typedef enum		e_lextype
  {
    DELIM,
    REDIR,
    WORD,
    PAR,
    QUOTE,
    DQUOTE,
    BACKQUOTE,
    AND
  }			t_lextype;

/*
** Structure that store a lexical element
** in order to be inserted in a list.
*/
typedef struct		s_lexelem
{
  struct s_lexelem	*next;
  struct s_lexelem	*prev;
  enum e_lextype     	type;
  char			*elem;
}			t_lexelem;

/*
** Structure that stores a lexical list
** of elements.
*/
typedef struct		s_lexlist
{
  struct s_lexelem	*head;
  struct s_lexelem	*tail;
  int			keys;
}			t_lexlist;

/*
** =============== Functions Definitions ===============
*/

/*
** lexer_new/types_tests.c
*/
int		func_exists(t_sllist **env, char *func);
int		file_exists(t_sllist **env, char *str);
int		is_option(char *str);
int		is_token(char *str);
int		is_arg(t_sllist **env, char *str);

/*
** lexer_new/types_verif.c
*/
int		func_lexic(t_list *list, int pos);
int		arg_lexic(t_sllist **env, t_list *list, int pos);
int		option_lexic(t_sllist **env, t_list *list, int pos);
int		token_lexic(t_list *prec_list, char *token);
int		lex_is_correct(t_sllist **env, t_list *exec_list);

/*
** lexer_new/lexer_funcs.c
*/
t_lextype	get_lextype(char a, char b, char c);
int		is_redirection(char a, char b);
int		is_delim(char a, char b);

/*
** lexer_new/lexlist_core.c
*/
t_lexlist	*init_lexlist(void);
t_lexelem	*fill_lexelem(char *elem, t_lextype type);
void		free_lexlist(t_lexlist *list, int flag);

/*
** lexer_new/lexlist_funcs.c
*/
int		insert_first_elem(t_lexlist *lexlist, t_lexelem *lexelem);
int		insert_in_lexlist(t_lexlist *lexlist, t_lexelem *lexelem);
int		del_first_lexelem(t_lexlist *lexlist);

/*
** lexer/spacialized_size.c
*/
int     	get_stdin_newsize(char *str);

/*
** lexer/spaces_management.c
*/
int		prec_space(char p_proec, char prec, char pos, char next);
int		next_space(char pos, char next, char n_next);

/*
** lexer/spacialize.c
*/
char		*spacialize_string(char *std_in);

/*
** lexer_new/quote_management.c
*/
char		*manage_quote(char *std_in, int *pos);

/*
** lexer_new/lexer_funcs.c
*/
t_lexelem	*get_next_lexelem(char *std_in, int *pos, t_lexlist **lexlist);

/*
** lexer_new/lexer.c
*/
t_lexlist	*get_lexlist(char *std_in);

#endif	       	/*LEXER_H*/
