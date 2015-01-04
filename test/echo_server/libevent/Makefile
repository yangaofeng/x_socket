echo_server : main.cc echo_server.cc x_socket.c
	g++ -Wall -g -levent -lpthread $^ -o $@

.PHONY : clean

clean :
	-rm echo_server *.o -f
