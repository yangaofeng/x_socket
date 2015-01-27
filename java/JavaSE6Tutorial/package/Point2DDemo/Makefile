
all: Point2D Point2DDemo Point2DDemo2 Point2DDemo3
	@echo "compile complete"
	
Point2DDemo: Point2DDemo.java
	javac $^

Point2DDemo2: Point2DDemo2.java
	javac $^

Point2DDemo3: Point2DDemo3.java
	javac $^

Point2D: Point2D.java
	javac -d . $^

test:
	@echo "Point2DDemo:"
	java Point2DDemo
	@echo "Point2DDemo2:"
	java Point2DDemo2
	@echo "Point2DDemo3:"
	java Point2DDemo3

.PHONY: clean

clean:
	@-rm *.class
	@-rm -rf onlyfun

