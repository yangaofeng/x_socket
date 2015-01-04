SRC = $(wildcard *.cc)

test : $(SRC)
	g++ -Wall -g -lglog -levent2 -lpthread $^ -o $@ 

.PHONY : clean

clean :
	-rm test -f

