#include <string.h>
#include <errno.h>
#include <stdio.h>
#include "observable_list.h"
#include "foreach.h"

void	get_callback(t_event_args arg)
{
  printf("%s: args = %lu\n", __FUNCTION__, *((long unsigned int *)arg));
}

void	add_callback(t_event_args arg)
{
  printf("%s: args->first = %s, args->second = %lu\n", __FUNCTION__, ((char *)((t_pair *)arg)->first), *((long unsigned int *)((t_pair *)arg)->second));
}

void	remove_callback(t_event_args arg)
{
  printf("%s: args = %lu\n", __FUNCTION__, *((long unsigned int *)arg));
}

int main()
{
  t_observable_list *ol = new(t_observable_list);

  if (!ol) {
    fprintf(stderr, "OL is null ! : %s\n", strerror(errno));
    return (1);
  }

  observable_list_attach(ol, OL_GET, get_callback);
  observable_list_attach(ol, OL_PUT, add_callback);
  observable_list_attach(ol, OL_POP, remove_callback);

  printf("j'insert a l'index 0 : 'phrase 0'\n");
  OLPUT(ol, "phrase 0", 0);
  printf("j'insert a l'index 0 : 'phrase 1'\n");
  OLPUT(ol, "phrase 1", 0);
  printf("j'insert a l'index 1 : 'phrase 2'\n");
  OLPUT(ol, "phrase 2", 1);

  printf("Taille de la liste : %lu\n", (long unsigned int)ol->list.size);

  FOREACH(char *, ph, ol,
	  printf("FOREACH: %s\n", ph);
  );

  printf("je recup a l'index 1 : %s\n", OLGET(char *, ol, 1));

  printf("je supprime à l'index 2\n");
  OLPOP(ol, 2);
  printf("je supprime à l'index 0\n");
  OLPOP(ol, 0);
  printf("je supprime à l'index 0\n");
  OLPOP(ol, 0);

  printf("Taille de la liste : %lu\n", (long unsigned int)ol->list.size);

  //Not necessary (presence of a garbage collector)
  delete(ol);

  return 0;
}
