event :
	make re -C examples/event-singleton_event_manager
	
event2 :
	make re -C examples/event2-observable_collection
	
exceptions :
	make re -C examples/exception_handling


event-clean :
	make fclean -C examples/event-singleton_event_manager
	
event2-clean :
	make fclean -C examples/event2-observable_collection
	
exception-clean :
	make fclean -C examples/exception_handling

all	: event event2 exceptions

clean : event-clean event2-clean exception-clean
