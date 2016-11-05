test: $(wildcard *.c)
	gcc -c $^
	ld a.o b.o -e main -o ab

.PHONY: clean

clean:
	rm *.o ab -f
