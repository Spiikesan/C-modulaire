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

#include "tcpnetc.h"

static void		tcp_del(t_object *ptr)
{
  t_tcpnetc	*t;

  if (!ptr)
    return ;
  t = (t_tcpnetc *)ptr;
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
  if (sock == (SOCKET)-1)
    {
      fprintf(stderr, "sock creating failed : %s\n", strerror(errno));
      return (-1);
    }
  return (sock);
}

CMETA_STRUCT_BUILD(t_tcpnetc_DEFINITION)
{
  t_tcpnetc		*t = newObject(t_tcpnetc, &tcp_del);
  SOCKADDR_IN		sin;
  struct hostent	*he;

  if (t) {
	  if (args.host && args.port)
	  {
		  t->socket = cross_tcp_create_socket();
		  if (t->socket > 0) {
			  memset((char *) &sin, 0, sizeof (struct sockaddr_in));
			  sin.sin_family = AF_INET;
			  sin.sin_port = htons(args.port);
			  if (!(he = gethostbyname(args.host)))
				{
				  fprintf(stderr, "Ip address conversion failed : %s\n", strerror(errno));
				  delete(t);
				  return (NULL);
				}
			  memcpy((char *)&sin.sin_addr.s_addr, (char *)he->h_addr, he->h_length);
			  if ((connect(t->socket, (struct sockaddr *)&sin,
						 sizeof(struct sockaddr_in))) == -1)
				{
				  fprintf(stderr, "Connecting to server failed : %s\n", strerror(errno));
				  delete(t);
				  return (NULL);
				}
		  } else
			  delete(t);
	  } else
		  delete(t);
  }
  return (t);
}
