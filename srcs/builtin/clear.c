#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<unistd.h>
#include	<dirent.h>

static int	rm_char(char *line, int pos)
{
  while (line[pos] && line[pos + 1])
    {
      line[pos] = line[pos + 1];
      pos++;
    }
  line[pos] = 0;
  return (0);
}

static int	rm_double_dash(char *path)
{
  int		i;
  int		len;

  len = strlen(path);
  i = 0;
  if (len > 1)
    {
      if (path[len - 1] == '/')
	{
	  path[len - 1] = 0;
	  return (1);
	}
      while (path[i] && path[i + 1])
	{
	  if (path[i] == '/' && path[i + 1] == '/')
	    {
	      rm_char(path, i);
	      return (1);
	    }
	  else
	    i++;
	}
    }
  return (0);
}

static int	is_double_dot(char *line, int pos)
{
  if (pos == 0)
    return (0);
  while (line[pos] == '/')
    pos++;
  if (!strncmp("..", line + pos, 3) ||
      !strncmp("../", line + pos, 3))
    return (1);
  return (0);
}

static int	rm_double_dot(char *line)
{
  int		pos;

  pos = 0;
  while (!is_double_dot(line, pos) && line[pos])
    pos++;
  if (line[pos])
    if (is_double_dot(line, pos))
      {
	while (line[pos] == '/' && line[pos])
	  pos--;
	pos++;
	while (line[pos] == '/' && line[pos])
	  rm_char(line, pos);
	rm_char(line, pos);
	rm_char(line, pos);
	pos--;
	while (line[pos] != '/' && line[pos])
	  pos--;
	pos++;
	while (line[pos] != '/' && line[pos])
	  rm_char(line, pos);
	return (1);
      }
  return (0);
}

int		clear_path(char *path)
{
  int		flag;

  flag = 1;
  while (flag)
    {
      flag = 0;
      flag += rm_double_dash(path);
      flag += rm_double_dot(path);
    }
  return (0);
}
