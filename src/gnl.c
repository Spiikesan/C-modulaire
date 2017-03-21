#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "gnl.h"

/*
** int	get_next_line(t_gnl g*, int fd, char **ret)
** return :
** 0 => no error, \n reached and ret filled
** 1 => no error, \n reached and ret filled, and str not null
** 2 => no error, \n not reached, ret = NULL
** 3 => EOF;
** 4 => malloc error
** 5 => read error
*/
static int	fill_str(t_gnl *g, char **ret, int fd)
{
  int	r;
  char	buff[257];

  if ((r = read(fd, buff, 256)) < 0)
    return (5);
  if (r == 0)
    return (3);
  if ((g->_buff = realloc(g->_buff, g->_buff_size + r + 1)) == NULL)
    return (4);
  buff[r] = 0;
  (g->_buff)[g->_buff_size] = 0;
  g->_buff = strcat(g->_buff, buff);
  g->_buff_size = strlen(g->_buff);
  if ((r = strcspn(g->_buff, "\n")) < g->_buff_size)
    {
      *ret = g->_buff;
      (*ret)[r] = 0;
      if ((g->_buff_size -= (r + 1)) > 0)
	g->_buff = strdup(&(g->_buff)[r + 1]);
      else
	g->_buff = NULL;
      return (g->_buff ? 1 : 0);
    }
  *ret = NULL;
  return (2);
}

int		get_next_line(t_gnl *g, int fd, char **ret)
{
  int		r;

  if (!g)
    return (3);
  if (g->_buff && (r = strcspn(g->_buff, "\n")) < g->_buff_size)
    {
      *ret = g->_buff;
      (*ret)[r] = 0;
      g->_buff_size -= (r + 1);
      if (g->_buff_size < 0)
	g->_buff_size = 0;
      if (g->_buff_size > 0)
	g->_buff = strdup(&(g->_buff)[r + 1]);
      else
	g->_buff = NULL;
      return ((g->_buff ? 1 : 0));
    }
  if (fd == -1)
    return (2);
  return (fill_str(g, ret, fd));
}
