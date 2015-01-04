http_server: $(wildcard *.cc) $(wildcard *.c)
	g++ -g -Wall -lpthread $^ -o $@

.PHONY : clean

clean:
	-rm -f http_server *.o

