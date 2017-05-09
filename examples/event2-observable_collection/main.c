#include <string.h>
#include <errno.h>
#include <stdio.h>
#include "observable_list.h"

void	get_callback(t_event_args arg)
{
  printf("%s: args = %lu\n", __FUNCTION__, *((size_t *)arg));
}

void	add_callback(t_event_args arg)
{
  printf("%s: args->first = %s, args->second = %lu\n", __FUNCTION__, ((char *)((t_pair *)arg)->first), *((size_t *)((t_pair *)arg)->second));
}

void	remove_callback(t_event_args arg)
{
  printf("%s: args = %lu\n", __FUNCTION__, *((size_t *)arg));
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

  printf("je recup a l'index 1 : %s\n", OLGET(char *, ol, 1));

  printf("je supprime à l'index 2\n");
  OLPOP(ol, 2);
  printf("je supprime à l'index 0\n");
  OLPOP(ol, 0);
  printf("je supprime à l'index 0\n");
  OLPOP(ol, 0);

  printf("Taille de la liste : %lu\n", ol->list.size);

  //Not necessary (presence of a garbage collector)
  delete(ol);

  return 0;
}
