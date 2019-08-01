NAME	= exception

CC	= gcc

CFLAGS	+= -W -Wall -Wextra -I../../include -Wno-missing-field-initializers

RM	= rm -f

SRC	= main.c			\
	  ../../src/exception_handler.c	\
	  ../../src/event_exception.c	\
	  ../../src/exception.c		\
	  ../../src/object.c		\
	  ../../src/list_modifiers.c	\
	  ../../src/list_accessors.c	\
	  ../../src/cmeta.c
	  

OBJ	= $(SRC:.c=.o)

$(NAME)	: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

all	: $(NAME)

clean	:
	$(RM) $(OBJ)

fclean	: clean
	$(RM) $(NAME) $(NAME).exe

re	: fclean all

test	: all
	valgrind ./$(NAME)
