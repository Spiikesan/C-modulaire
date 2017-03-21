#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#ifdef __linux__
# include <stdlib.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <netdb.h>
#endif

#include "tcpnetc.h"

void		tcp_del(void *ptr)
{
  t_tcpnetc	*t;

  if (!ptr)
    return ;
  t = ptr;
  shutdown(t->socket, 2);
#ifdef __linux__
  close(t->socket);
#elif _WIN32
  closesocket(t->socket);
  WSACleanup();
#endif
}

static void	cross_tcp_init(void)
{
#ifdef _WIN32
  WSADATA	wsa;
  int		err;

  err = WSAStartup(MAKEWORD(2, 2), &wsa);
  if (err < 0)
    {
      fprintf(stderr, "WSAStartup failed !\n");
      exit(EXIT_FAILURE);
    }
#endif
}

static int	cross_tcp_create_socket(void)
{
  SOCKET	sock;

  cross_tcp_init();
  errno = 0;
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1)
    {
      fprintf(stderr, "sock creating failed : %s\n", strerror(errno));
      return (-1);
    }
  return (sock);
}

t_tcpnetc		*t_tcpnetc_new(t_tcpnetc_init var)
{
  t_tcpnetc		*t;
  SOCKADDR_IN		sin;
  struct hostent	*he;

  if (!var.host || !var.port ||
      (t = newObject(t_tcpnetc, &tcp_del)) == NULL)
    return (NULL);
  if ((t->socket = cross_tcp_create_socket()) <= 0)
    return (NULL);
  memset((char *) &sin, 0, sizeof (struct sockaddr_in));
  sin.sin_family = AF_INET;
  sin.sin_port = htons(var.port);
  if (!(he = gethostbyname(var.host)))
    {
      fprintf(stderr, "Ip address conversion failed : %s\n", strerror(errno));
      return (NULL);
    }
  memcpy((char *)&sin.sin_addr.s_addr, (char *)he->h_addr, he->h_length);
  if (-1 == (connect(t->socket, (struct sockaddr *)&sin,
		     sizeof(struct sockaddr_in))))
    {
      fprintf(stderr, "Connecting to server failed : %s\n", strerror(errno));
      return (NULL);
    }
  return (t);
}
