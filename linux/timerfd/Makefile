SRC=$(wildcard *.c)
OBJ=$(SRC:%.c=%.o)
TARGET=timerfd


CXXFLAGS := -g -O0 -I./
LDFLAGS := -lrt

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CXXFLAGS) $< -c -o $@

%.d: %.c
	@$(CC) -MM $(CXXFLAGS) $< > $@.$$$$; \
		sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
		rm -f $@.$$$$

sinclude $(SRC:.c=.d)

.PHONY: clean

clean:
	rm $(TARGET) $(OBJ) *.d -f

