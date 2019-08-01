#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#ifdef __linux__
#include <execinfo.h>
#endif
#include "raise.h"
#include "exception.h"

static char	*get_stack_trace()
{
#ifdef __linux__
	void		*buffer[MAX_BT];
	char		**strings;
	char		*sstrace;
	int		i;
	int		n;
	int		len = 0;

	n = backtrace(buffer, MAX_BT);
	strings = backtrace_symbols(buffer, n);
	for (i = 0, len = 0; i < n; ++i) {
		len += strlen(strings[i]) + 1;
	}
	len += 20;
	sstrace = malloc(len + 1);
	snprintf(sstrace, 20, "--- (depth %d) ---", n);
	for (i = 0; i < n; ++i) {
		strcat(sstrace, "\n");
		strcat(sstrace, strings[i]);
	}
	free(strings);
	return (sstrace);
#else
	return strdup("No stack trace available.");
#endif
}

static void	Exception_del(t_object *ptr)
{
	Exception *self = (Exception *)ptr;
	if (self->buffer)
		free(self->buffer);
	if (self->stack)
		free(self->stack);
	self->buffer = NULL;
	self->stack = NULL;
	self->file = NULL;
	self->msg = NULL;
}

CMETA_STRUCT_BUILD(Exception_DEFINITION)
{
	Exception *self = newObject(Exception, &Exception_del);

	if (self) {
		self->msg = args.msg ? args.msg : "Exception";
		self->buffer = NULL;
		self->file = args.file ? args.file : "Unspecified file";
		self->line = args.line;
		self->stack = get_stack_trace();
	}
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
	snprintf(self->buffer, len, "Exception occured !\nFILE: %s: LINE: %lu; %s\n%s", self->file, (unsigned long)self->line, self->msg, self->stack);
	return (self->buffer);
}
