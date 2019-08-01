CC	= gcc

CFLAGS	+= -std=gnu99 -W -Wall -Wextra -Werror -Iinclude -Wno-missing-field-initializers

event :
	make re -C examples/event-singleton_event_manager
	
event2 :
	make re -C examples/event2-observable_collection
	
exceptions :
	make re -C examples/exception_handling

introspection :
	make re -C examples/introspection
	
binary_options :
	make re -C examples/binary_options
	
	
event-clean :
	make fclean -C examples/event-singleton_event_manager
	
event2-clean :
	make fclean -C examples/event2-observable_collection
	
exception-clean :
	make fclean -C examples/exception_handling
	
introspection-clean :
	make fclean -C examples/introspection

binary_options-clean :
	make fclean -C examples/binary_options

all	: event event2 exceptions introspection binary_options

clean : event-clean event2-clean exception-clean introspection-clean binary_options-clean
	$(RM) src/*.o buildObjs.so
	
SRC = $(wildcard src/*.c)

OBJ	= $(SRC:.c=.o)

buildObjs-clean:
	rm -f src/*.o buildObjs.so

buildObjs: buildObjs-clean $(OBJ)
	$(CC) -shared $(CFLAGS) $(LDFLAGS) $(OBJ) -lWs2_32 -o buildObjs.so
	
