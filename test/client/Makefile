SRC=$(wildcard *.c) ../../x_socket.c
OBJ=$(SRC:%.c=%.o)
TARGET=client
#TARGET=test.so # for make  so


CFLAGS := -g -O0 -I../../
#CXXFLAGS := -g -O0 -fPIC -Wall
LDFLAGS := 
#LDFLAGS := -Wl,-rpath=/home/s/lib

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $@
#	$(CXX) -shared $(LDFLAGS) $^ -o $@ # for make so

%.o: %.c
	$(CC) $(CFLAGS) $< -c -o $@

%.d: %.c
	@$(CC) -MM $(CFLAGS) $< > $@.$$$$; \
		sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
		rm -f $@.$$$$

sinclude $(SRC:.c=.d)

.PHONY: clean

clean:
	rm $(TARGET) $(OBJ) *.d -f

