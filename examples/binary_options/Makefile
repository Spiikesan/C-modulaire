NAME	= binary_options

CC	= gcc

CFLAGS	+= -W -Wall -Wextra -I../../include -std=gnu99 -g3 -Wno-missing-field-initializers

RM	= rm -f

SRC	= main.c			\
	  ../../src/get_opt.c		\
	  ../../src/opt_types.c		\
	  ../../src/object.c	\
	  ../../src/vector_modifiers.c \
	  ../../src/vector_accessors.c \
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
