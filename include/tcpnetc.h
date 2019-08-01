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

# include "object.h"

# define t_tcpnetc_DEFINITION	\
	t_tcpnetc,					\
	(pChar, host),				\
	(uShort, port),				\
	(SOCKET, socket)


CMETA_STRUCT_DEF(t_tcpnetc_DEFINITION);

#endif /* !TCPNETC_H_ */
