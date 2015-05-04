aggs: $(wildcard *.cc)
	g++ -g -O0 $^ -o $@ -lcurl -lgflags

.PHONY:clean

clean:
	@-rm aggs
	@-rm *.json -f
