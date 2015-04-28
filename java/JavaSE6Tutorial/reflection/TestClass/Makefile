
all: TestClass LoadClassTest
	@echo "complete compile"

TestClass: TestClass.java
	javac $^

LoadClassTest: LoadClassTest.java
	javac $^

.PHONY: clean test

clean:
	rm *.class

test:
	java LoadClassTest
