NAME	= exception

CC	= gcc

CFLAGS	+= -W -Wall -Werror -Wextra -rdynamic -I../../include

RM	= rm -f

SRC	= main.c			\
	  ../../src/exception_handler.c	\
	  ../../src/event_exception.c	\
	  ../../src/exception.c		\
	  ../../src/new.c		\
	  ../../src/list_modifiers.c	\
	  ../../src/list_accessors.c

OBJ	= $(SRC:.c=.o)

$(NAME)	: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

all	: $(NAME)

clean	:
	$(RM) $(OBJ)

fclean	: clean
	$(RM) $(NAME)

re	: fclean all

test	: all
	valgrind ./$(NAME)
