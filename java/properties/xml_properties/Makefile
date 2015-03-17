TARGET:=LoadSampleXML

$(TARGET): $(wildcard *.java)
	javac $^

.PHONY: clean

test:
	java $(TARGET)

clean:
	@rm -f *.class

