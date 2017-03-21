#ifndef RAISE_H
# define RAISE_H

# include <stdio.h>
# include <stdlib.h>

# define raise(msg)							\
  { fprintf(stderr, "%s: %u: %s\n", __FILE__, __LINE__, msg); abort(); }

#endif
