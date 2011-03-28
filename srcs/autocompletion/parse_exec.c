#include	<stdlib.h>
#include	<string.h>
#include	<ctype.h>
#include	<unistd.h>
#include	<dirent.h>
#include	<sys/types.h>

#include	"42sh.h"
#include	"my.h"
#include	"lexer.h"
#include	"termc.h"
#include	"auto.h"

void		check_if_space(t_link *buff)
{
  char		*new;

  if (is_space(buff->data))
  {
    new = add_quote(buff);
    free(buff->data);
    buff->data = new;
  }
}

t_termc		*manage_auto(t_list *new, t_termc *cmd, t_tutils *utils)
{
  int		i;
  t_com		*buff;
  t_com		*b_buff;
  
  if (new->size == 1)
  {
    buff = cmd->end;
    i = cmd->nb_char;
    while (buff && i > 0 && (isupper(buff->c) || islower(buff->c) ||
	   buff->c == '-' || buff->c == '_' ))
    {
      b_buff = buff;
      buff = buff->prev;
      del_char(cmd, b_buff);
      i--;
    }
    return (my_listcat(cmd, new));
  }
  else if (new->size >= 1)
  {
    check_semi_complet(cmd, new);
    echo_completion(cmd, utils, new);
  }
  freemylist(new);
  return (cmd);
}

t_list		*select_exec(t_list *binary, char *str)
{
  t_list	*new_bin;
  t_link	*buff;
  int		nb;
  int		i;
  
  new_bin = xmalloc(sizeof(*new_bin));
  init_list(new_bin);
  buff = binary->head;
  i = strlen(str);
  nb = 0;
  while (i && (isupper(str[i - 1]) || islower(str[i - 1]) ||
	str[i - 1] == '-' || str[i - 1] == '_' ))
  {
    i--;
    nb++;
  }
  while (buff)
  {
    if (!strncmp(str + i, buff->data, nb))
      insert_end(new_bin, buff->data);
    buff = buff->next;
  }
  return (new_bin);
}

t_list		*parse_ex(t_list *path)
{
  t_link	*path_b;
  t_list	*binary;
  DIR		*dir;
  struct dirent	dir_data;
  struct dirent	*dir_res;

  path_b = NULL;
  binary = xmalloc(sizeof(*binary));
  init_list(binary);
  if (path)
    path_b = path->head;
  while (path_b)
    {
      if (!access(path_b->data, X_OK))
	{
	  dir = xopendir(path_b->data);
	  while (!xreaddir_r(dir, &dir_data, &dir_res) && dir_res != NULL)
	    if (strncmp(dir_data.d_name, ".", 1))
	      insert_end(binary, dir_data.d_name);
	  xclosedir(dir);
	}
      path_b = path_b->next;
    }
  sort_list(binary, path);
  return (binary);
}
