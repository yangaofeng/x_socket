SRC=$(wildcard *.cc)
OBJ=$(SRC:%.cc=%.o)
TARGET=hello


CXXFLAGS := -g -O0 -I./
LDFLAGS := 

$(TARGET): $(OBJ)
	$(CXX) $(LDFLAGS) $^ -o $@

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

