event :
	make re -C examples/event-singleton_event_manager
	
event2 :
	make re -C examples/event2-observable_collection
	
exceptions :
	make re -C examples/exception_handling

introspection :
	make re -C examples/introspection
	
event-clean :
	make fclean -C examples/event-singleton_event_manager
	
event2-clean :
	make fclean -C examples/event2-observable_collection
	
exception-clean :
	make fclean -C examples/exception_handling
	
introspection-clean :
	make fclean -C examples/introspection

all	: event event2 exceptions introspection

clean : event-clean event2-clean exception-clean introspection-clean
