#ifndef TCPNETC_H_
# define TCPNETC_H_

# ifdef __linux__
#  include <arpa/inet.h>
#  define INVALID_SOCKET -1
#  define SOCKET_ERROR -1
#  define closesocket(s) close(s)
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;
# elif _WIN32
#  include <winsock2.h>
# endif

# include "new.h"

typedef struct	s_tcpnetc_init
{
  char		*host;
  int		port;
}		t_tcpnetc_init;

typedef struct	s_tcpnetc
{
  t_object	__obj__;
  SOCKET	socket;
}		t_tcpnetc;

t_tcpnetc		*t_tcpnetc_new(t_tcpnetc_init var);

#endif /* !TCPNETC_H_ */
