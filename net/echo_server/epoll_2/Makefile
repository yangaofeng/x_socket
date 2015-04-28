SRC=$(wildcard *.cc)
CSRC=$(wildcard *.c)
OBJ:=$(SRC:%.cc=%.o)
OBJ+=$(CSRC:%.c=%.o)

TARGET=http_server

CC := gcc
CXX := g++

CFLAGS := -g -O0 -I./
CXXFLAGS := -g -O0 -I./
LDFLAGS := -lpthread

$(TARGET): $(OBJ)
	$(CXX) $(LDFLAGS) $^ -o $@

%.o: %.cc
	$(CXX) $(CXXFLAGS) $< -c -o $@

%.d: %.cc
	@$(CXX) -MM $(CXXFLAGS) $< > $@.$$$$; \
		sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
		rm -f $@.$$$$

%.o: %.c
	$(CC) $(CFLAGS) $< -c -o $@

%.d: %.c
	@$(CXX) -MM $(CXXFLAGS) $< > $@.$$$$; \
		sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
		rm -f $@.$$$$

sinclude $(SRC:.cc=.d)
sinclude $(CSRC:.c=.d)

.PHONY: clean

clean:
	@rm $(TARGET) $(OBJ) *.d -f

