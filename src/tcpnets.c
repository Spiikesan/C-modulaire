#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#ifdef __linux__
# include <stdlib.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <netdb.h>
#elif _MSC_VER
#pragma comment(lib,"Ws2_32.lib")
#endif

#include "tcpnets.h"

static void		tcp_del(t_object *ptr)
{
  t_tcpnets	*t;

  if (!ptr)
    return ;
  t = (t_tcpnets *)ptr;
  if (t->socket > 0) {
	  shutdown(t->socket, 2);
#ifdef __linux__
	  close(t->socket);
  }
#elif _WIN32
	  closesocket(t->socket);
  }
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
    exit(1);
#endif
}

static int	cross_tcp_create_socket(struct protoent *pe)
{
  if (!pe)
    return (-1);
  cross_tcp_init();
  errno = 0;
  return (socket(AF_INET, SOCK_STREAM, pe->p_proto));
}

CMETA_STRUCT_BUILD(t_tcpnets_DEFINITION)
{
  t_tcpnets		*t = newObject(t_tcpnets, &tcp_del);
  SOCKADDR_IN		sin;
#ifdef __linux__
  const int		optval = 1;
#endif

  if (t) {
	  if (args.port > 0) {
		  memset((char *) &sin, 0, sizeof (struct sockaddr_in));
		  sin.sin_family = AF_INET;
		  sin.sin_port = htons(args.port);
		  sin.sin_addr.s_addr = INADDR_ANY;
		  if ((t->socket = cross_tcp_create_socket(getprotobyname("TCP"))) <= 0 ||
#ifdef __linux__
			  setsockopt(t->socket, SOL_SOCKET, SO_REUSEPORT,
				 &optval, sizeof(optval)) == -1 ||
#endif
			  bind(t->socket, (const struct sockaddr *)&sin, sizeof(sin)) == -1 ||
			  listen(t->socket, (args.max_queue ? args.max_queue : 5)) == -1)
			{
			  delete(t);
			  return (NULL);
			}
	  } else
		  delete(t);
  }
  return (t);
}
