SRC=$(wildcard *.cc)
OBJ=$(SRC:%.cc=%.o)
TARGET=test


CXXFLAGS := -g -O0 -I./ -I/usr/include/boost141
LDFLAGS := -L/usr/lib64/boost141/ -lboost_thread-mt
#LDFLAGS := -Wl,-rpath=/home/s/lib

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

