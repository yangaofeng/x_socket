SRC=$(wildcard *.cc)
OBJ=$(SRC:%.cc=%.o)
TARGET=dispatcher.so


CXXFLAGS := -g -O0 -fPIC -Wall -I/home/s/include
LDFLAGS := 

$(TARGET): $(OBJ)
	$(CXX) -shared $(LDFLAGS) $^ -o $@

%.o: %.cc
	$(CXX) $(CXXFLAGS) $< -c -o $@

%.d: %.cc
	@$(CXX) -MM $(CXXFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

sinclude $(SRC:.cc=.d)

.PHONY: clean

clean:
	@rm $(TARGET) $(OBJ) *.d -f
