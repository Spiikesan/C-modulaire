NAME	= introspection

CC	= gcc

CFLAGS	+= -W -Wall -Wextra -std=gnu99 -g3 -I../../include -Wno-missing-field-initializers

RM	= rm -f

SRC	= main.c				\
	  intro.c				\
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
	valgrind ./$(NAME)
