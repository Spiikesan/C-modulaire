#ifndef TCPNETS_H_
# define TCPNETS_H_

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

# include "object.h"

# define t_tcpnets_DEFINITION	\
	t_tcpnets,					\
	(uShort, port),				\
	(uInt, max_queue),			\
	(SOCKET, socket)

CMETA_STRUCT_DEF(t_tcpnets_DEFINITION);

#endif /* !TCPNETS_H_ */
