SRC=$(wildcard *.cc)
OBJ=$(SRC:%.cc=%.o)
TARGET=test
#TARGET=test.so # for make  so


CXXFLAGS := -g -O0 -I./ 
#CXXFLAGS := -g -O0 -fPIC -Wall
LDFLAGS := -lpthread
#LDFLAGS := -Wl,-rpath=/home/s/lib

$(TARGET): $(OBJ)
	$(CXX) $(LDFLAGS) $^ -o $@
#	$(CXX) -shared $(LDFLAGS) $^ -o $@ # for make so

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

