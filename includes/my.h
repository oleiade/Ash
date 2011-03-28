#ifndef		__MY_H__
# define	__MY_H__

/*
** =============== MACROS ===============
*/
# define	IS_PRINTABLE(c) ((c != '|') && (c != '<') && \
				 (c != '>') && (c != ';') && \
				 (c != ' ') && (c != '*') && \
				 (c != '&'))

# define	ERR_PIPE	"Error while trying to make a pipe !\n"

/*
** =============== TYPE DEFIITIONS ===============
*/

/*
** Double linked lists definition.
** including each node data hash,
** in order to optimize the
** lists searching functions.
*/
typedef struct		s_link
{
  char			*data;
  struct s_link		*next;
  struct s_link		*previous;
}			t_link;

typedef struct		s_list
{
  int			size;
  struct s_link		*tail;
  struct s_link		*head;
}			t_list;

/*
** Structure that permitts to organizely
** store the links searching needeed vars.
*/
typedef struct		s_searchvars
{
  int			head_pos;
  int			tail_pos;
  t_link		*asc_ptr;
  t_link		*desc_ptr;
}			t_searchvars;

/*
** A simple ptr lists,
** used by the double linked lists
** search links functions.
*/
typedef struct		s_ptrlist
{
  int			pos;
  char			*data_ptr;
  struct s_ptrlist	*previous_ptr;
}			t_ptrlist;

/*
** String funcs
*/

char		*my_strnamecpy(char *, char *);
int		my_str_isalpha(char *);
int		my_memset(char *, char, int);
int		my_str_isalpha(char *);
int		is_printable(char *);
char		*remove_ex_char(char *, int);

/*
** String modifications functions
*/
char		*remove_spaces(char *str);

/*
** Errors management functions
*/

int		my_put_errno(int);
void		puterr_exec(char *);
void		my_putstr(char *c);

/*
** Int related functions
*/

int		my_put_errno(int);

/*
** Str_to_word_tab dependencies functions
*/

int		ins_str(int *, int *, char *, char *, int);
char		*cut_line(char *);
char		*get_word(char *, int *);
char		**line_to_argv(char *);
int		nb_spec_char(char *);
int		nb_word(char *);
int		word_size(char *);
int		free_argv(char **);

/*
** Xfuncs, verify the system calls return
*/

void		*xmalloc(unsigned int);
int		xdup2(int, int);
int		xread(int, void *, int);
int		xfork(void);
int		xpipe(int pipe[2]);
int		xwait(void);
int		xwaitpid(unsigned int, int *, int);
int		xexecve(char **, char **, char *);
int		xclose(int);
int		xwrite(int, const void *, int);
int		xopen(char *, int, int);
struct dirent	*xreaddir(DIR *);
DIR		*xopendir(char *);
int		xreaddir_r(DIR *, struct dirent *,
			   struct dirent **);
void		xclosedir(DIR *);

/*
** Signal functions definition
*/
void		disable_sig(void);
void		enable_sig(void);
char		*my_strsignal(int);

/*
** Double linked lists functions
** prototypes.
*/
t_link 		*fill_link(t_link *link, char *data);
void   		init_list(t_list *list);
void   		remove_dlist(t_list *list);
int    		add_first_link(t_list *list, char *data);
int    		insert_beginning(t_list *list, char *data);
int    		insert_end(t_list *list, char *data);
int    		insert_bef_xlink(t_list *list, char *data, int x);
int    		insert_after_xlink(t_list *list, char *data, int x);
int    		del_dlist_id(t_list *list, int pos);
int    		print_list(t_list *list);
char   		*update_link(t_list *list, int pos, char *str);
char   		*get_xlink(t_list *list, int x);
t_list 		*my_wordlist(char *src, char delim1, char delim2);
void   		freemylist(t_list *list);

/*
** Others
*/
int		bypass_spaces(char *str, int pos);

#endif		/*__MY_H__*/
