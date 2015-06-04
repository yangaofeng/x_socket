SRC=$(wildcard *.c)
OBJ=$(SRC:%.c=%.o)
TARGET=test


CFLAGS := -g -O0 -I./
LDFLAGS := 

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

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

