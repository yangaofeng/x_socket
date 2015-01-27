
all: Point2D Point2DDemo Point2DDemo2
	@echo "compile complete"
	
Point2DDemo: ./src/Point2DDemo.java
	javac -cp ./class/onlyfun.jar -d ./class $^

Point2DDemo2: ./src/Point2DDemo2.java
	javac -cp ./class/onlyfun.jar -d ./class $^

Point2DDemo3: ./src/Point2DDemo3.java
	javac -cp ./class/onlyfun.jar -d ./class $^

Point2D: ./src/Point2D.java
	@-mkdir class
	@-mkdir ./bin
	javac -d ./bin $^
	jar cvf onlyfun.jar -C ./bin .
	mv onlyfun.jar ./class
	@rm -rf bin

test:
	@echo "Point2DDemo:"
	java -cp ./class:./class/onlyfun.jar Point2DDemo
	@echo "Point2DDemo2:"
	java -cp ./class:./class/onlyfun.jar Point2DDemo2
	@echo "Point2DDemo3:"
	java -cp ./class:./class/onlyfun.jar Point2DDemo3

.PHONY: clean test

clean:
	@-rm -rf class
