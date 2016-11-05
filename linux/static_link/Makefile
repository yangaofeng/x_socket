hello: libhello.a libreal_hello.a
	gcc -c main.c
	gcc -o hello main.o ./libhello.a ./libreal_hello.a

test: libhello.a libreal_hello.a
	gcc -c main.c
	gcc -o test main.o libreal_hello.a libhello.a 

libhello.a:
	gcc -c hello.c
	ar -rs $@ hello.o

libreal_hello.a:
	gcc -c real_hello.c
	ar -rs $@ real_hello.o

.PHONY: clean

clean:
	rm hello *.o test *.a -f
