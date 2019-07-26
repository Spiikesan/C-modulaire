NAME	= introspection

CC	= gcc

CFLAGS	+= -W -Wall -Wextra -I../../include -Wno-missing-field-initializers

RM	= rm -f

SRC	= main.c				\
	  intro.c				\
	  ../../src/object.c	\
	  ../../src/CMeta.c

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
