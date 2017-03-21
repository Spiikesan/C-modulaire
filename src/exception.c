#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <execinfo.h>
#include "raise.h"
#include "exception.h"

static char	*get_stack_trace()
{
  void		*buffer[MAX_BT];
  char		**strings;
  char		*sstrace;
  int		i;
  int		n;
  int		len;

  n = backtrace(buffer, MAX_BT);
  strings = backtrace_symbols(buffer, n);
  for (i = 0, len = 0; i < n; ++i) {
    len += strlen(strings[i]) + 1;
  }
  len += 20;
  sstrace = malloc(len);
  snprintf(sstrace, 20, "--- (depth %d) ---", n);
  for (i = 0; i < n; ++i) {
    strcat(sstrace, "\n");
    strcat(sstrace, strings[i]);
  }
  free(strings);
  return (sstrace);
}

static void	Exception_del(void *ptr)
{
 Exception *self = ptr;

  free(self->buffer);
  free(self->stack);
  self->buffer = NULL;
  self->stack = NULL;
  self->file = NULL;
  self->msg = NULL;
}

Exception	*Exception_new(Exception_init var)
{
  Exception *self;

  if ((self = newObject(Exception, &Exception_del)) == NULL)
    return (NULL);
  self->msg = var.msg ? var.msg : "Exception";
  self->buffer = NULL;
  self->file = var.file ? var.file : "Unspecified file";
  self->line = var.line;
  self->stack = get_stack_trace();
  return (self);
}

/* Can only have a Exception class */
char const	*Exception_to_string(t_object *this)
{
  Exception	*self = (Exception *)this;
  size_t	len;

  if (self->buffer)
    return (self->buffer);
  len = 36 + strlen(self->msg) + strlen(self->file) + 11 + strlen(self->stack);
  if ((self->buffer = malloc(len)) == NULL)
    raise("Out of memory");
  snprintf(self->buffer, len, "Exception occured !\nFILE: %s: LINE: %lu; %s\n%s", self->file, self->line, self->msg, self->stack);
  return (self->buffer);
}
