CC = gcc 
CFLAGS = -Wall -g -std=c99

DEF_ARGS = airports.txt schedules.txt routes.txt

RouteTime: timeHM.o flights.o RouteTime.o
	$(CC) -o $@ timeHM.o flights.o RouteTime.o

run:	RouteTime
	./RouteTime $(DEF_ARGS)

flights-memcheck:	RouteTime
	valgrind --tool=memcheck --leak-check=full --dsymutil=yes --track-origins=yes ./RouteTime $(DEF_ARGS)

%.o: %.c
	$(CC) -c $(CFLAGS) $<

clean:
	rm -rf timeHM.o flights.o RouteTime.o RouteTime RouteTime.dSYM