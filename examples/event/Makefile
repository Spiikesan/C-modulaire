NAME	= events

CC	= gcc

CFLAGS	+= -W -Wall -Wextra -I../../include -DEVENT_SINGLETON

RM	= rm -f

SRC	= main.c			\
	  my_string_event.c		\
	  ../../src/event_manager.c	\
	  ../../src/circularBuff.c	\
	  ../../src/new.c

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
