#include	<stdlib.h>
#include	<stdio.h>
#include	<dirent.h>
#include	<string.h>

#include	"42sh.h"
#include	"lexer.h"

static char	*getvar(char *str)
{
  char		*var;
  int		i;

  i = 0;
  var = xmalloc(sizeof(char) * (strlen(str) + 1));
  while (*str && *str != ' ' && *str != '\t')
    {
      var[i++] = *str;
      str++;
    }
  var[i] = 0;
  return (var);
}

static char	*my_realloc(char *data, unsigned int size)
{
  char		*new;
  int		j;
  int		i;
  
  j = 0;
  i = 0;
  new = xmalloc(sizeof(char) * (strlen(data) + size + 1000));
  while (data[i])
    {
      new[j] = data[i];
      i++;
      j++;
    }
  new[j] = 0;
  free(data);
  return (new);
}

static char	*setvar_dquote(char *str, t_sllist *myenv)
{
  int		i;
  int		j;
  int		k;
  char		*new;
  char		*vardata;
  char		*varname;

  i = 0;
  j = 0;
  new = xmalloc(sizeof(*new) * (strlen(str) + 1));
  while (str[i])
    {
      if (str[i] == '$')
	{
	  k = 0;
	  varname = getvar(str + i + 1);
	  vardata = my_getenv(varname, myenv);
	  free(varname);
	  new = my_realloc(new, sizeof(*new) * strlen(vardata));
	  while (vardata[k])
	    new[j++] = vardata[k++];
	  while (str[i] != ' ' && str[i] != '\t' && str[i])
	    i++;
	}
      new[j++] = str[i++];
    }
  free(str);
  new[j] = 0;
  return (new);
}

int		setvar_lexlist(t_lexlist *list, t_sllist *myenv)
{
  t_lexelem	*cur;
  char		*new;

  cur = list->head;
  while (cur)
    {
      if (cur->type == WORD && cur->elem[0] == '$')
	{
	  new = strdup(my_getenv(cur->elem + 1, myenv));
	  if (!strcmp(new, ""))
	    fprintf(stderr, "%s : %s\n", cur->elem + 1, ERR_VAR);
	  free(cur->elem);
	  cur->elem = new;
	}
      else if (cur->type == DQUOTE)
	cur->elem = setvar_dquote(cur->elem, myenv);
      cur = cur->next;
    }
  return (0);
}
