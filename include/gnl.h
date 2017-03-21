#ifndef GNL_H_
# define GNL_H_

typedef struct	s_gnl
{
  long		_buff_size;
  char		*_buff;
}		t_gnl;

int	get_next_line(t_gnl *g, int fd, char **ret);

#endif /* !GNL_H_ */
