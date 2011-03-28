#ifndef		__STRUCT_H_
# define	__STRUCT_H_

/*
** Simple linked chains structure
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

#endif
