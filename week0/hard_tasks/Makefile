.PHONY = clean

analizator: analizator.o getifconf.o getsock_recv.o
	gcc $^ -g -o $@

%.o: %.c
	gcc -c $^

clean:
	rm -f *.o
	rm -f ./analizator

