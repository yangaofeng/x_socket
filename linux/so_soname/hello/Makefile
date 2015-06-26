SRC=$(wildcard *.c)
OBJ=$(SRC:%.c=%.o)

SO=libhello.so
MAJOR=1
MINOR=0
BUILD=0

TARGET=$(SO).$(MAJOR).$(MINOR).$(BUILD)

CFLAGS := -g -O0 -fPIC -Wall
LDFLAGS := -shared -Wl,-soname,$(SO).$(MAJOR)

$(TARGET): $(OBJ)
	$(CXX) $(LDFLAGS) $^ -o $@
	ln -s $(TARGET) $(SO)
	ln -s $(TARGET) $(SO).$(MAJOR)

%.o: %.c
	$(CC) $(CFLAGS) $< -c -o $@

%.d: %.c
	@$(CC) -MM $(CFLAGS) $< > $@.$$$$; \
		sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
		rm -f $@.$$$$

sinclude $(SRC:.c=.d)

.PHONY: clean

clean:
	rm $(TARGET) $(OBJ) *.d *.so *.so.* -f

