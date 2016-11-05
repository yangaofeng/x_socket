all: say_hello say_hi test

say_hello: say_hello.c
	gcc -c $^ -o say_hello.o
	ar -rcs libsay_hello.a say_hello.o

say_hi: say_hi.c
	gcc -c $^ -fPIC -o say_hi.o 
	gcc -shared -o libsay_hi.so say_hi.o

test: main.c
	gcc -o test $^ -L. -lsay_hi ./libsay_hello.a -Wl,-rpath=./

.PHONY: clean

clean:
	rm -f *.a *.so *.o test
