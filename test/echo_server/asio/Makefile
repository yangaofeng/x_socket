http_server: main.cc
	g++ -I/usr/include/boost141/ -lpthread -L/usr/lib64/boost141/ -lboost_system-mt $^ -o $@

.PHONY: clean

clean:
	-rm -f http_server *.o
