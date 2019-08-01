NAME	= events

CC	= gcc

CFLAGS	+= -W -Wall -Wextra -I../../include -std=gnu99 -DEVENT_SINGLETON -g3 -Wno-missing-field-initializers

RM	= rm -f

SRC	= main.c			\
	  ../../src/event_manager.c	\
	  ../../src/list_modifiers.c	\
	  ../../src/list_accessors.c	\
	  ../../src/map_modifiers.c	\
	  ../../src/map_accessors.c	\
	  ../../src/pair.c		\
	  ../../src/object.c	\
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
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)
