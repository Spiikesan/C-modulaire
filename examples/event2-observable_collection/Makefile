NAME	= events2

CC	= gcc

CFLAGS	+= -W -Wall -Wextra -I../../include -std=gnu99 -g3 -Wno-missing-field-initializers

RM	= rm -f

SRC	= main.c			\
	  observable_list_modifiers.c	\
	  observable_list_accessors.c	\
	  observable_list_events.c	\
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
