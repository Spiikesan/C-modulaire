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

#include "tcpnets.h"

void		tcp_del(void *ptr)
{
  t_tcpnets	*t;

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
    exit(84);
#endif
}

static int	cross_tcp_create_socket(struct protoent *pe)
{
  SOCKET	sock;

  if (!pe)
    return (-1);
  cross_tcp_init();
  errno = 0;
  sock = socket(AF_INET, SOCK_STREAM, pe->p_proto);
  if (sock == -1)
    return (-1);
  return (sock);
}

t_tcpnets		*t_tcpnets_new(t_tcpnets_init var)
{
  t_tcpnets		*t;
  SOCKADDR_IN		sin;
  const int		optval = 1;

  if (!var.port ||
      (t = newObject(t_tcpnets, &tcp_del)) == NULL)
    return (NULL);
  memset((char *) &sin, 0, sizeof (struct sockaddr_in));
  sin.sin_family = AF_INET;
  sin.sin_port = htons(var.port);
  sin.sin_addr.s_addr = INADDR_ANY;
  if ((t->socket = cross_tcp_create_socket(getprotobyname("TCP"))) <= 0 ||
#ifdef __linux__
      setsockopt(t->socket, SOL_SOCKET, SO_REUSEPORT,
		 &optval, sizeof(optval)) == -1 ||
#endif
      bind(t->socket, (const struct sockaddr *)&sin, sizeof(sin)) == -1 ||
      listen(t->socket, (var.max_queue ? var.max_queue : 5)) == -1)
    {
      if (t->socket != -1)
	close(t->socket);
      return (NULL);
    }
  return (t);
}
