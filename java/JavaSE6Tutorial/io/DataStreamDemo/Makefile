
all: Member DataStreamDemo
	@echo "compile complete"
	
Member: Member.java
	javac -d . $^

DataStreamDemo: DataStreamDemo.java
	javac -d . $^

test:
	@echo "DataStreamDemo"
	java onlyfun.caterpillar.DataStreamDemo m.dat

.PHONY: clean test

clean:
	@-rm -rf onlyfun
	@-rm -f m.dat
