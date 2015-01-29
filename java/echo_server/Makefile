TARGET:=all

$(TARGET): NIOServer.class NIOClient.class
	@echo "compile compleate"

NIOServer.class: NIOServer.java
	javac -d . $^

NIOClient.class: NIOClient.java
	javac -d . $^

test: $(TARGET)
	java cn.nio.NIOServer
	java cn.nio.NIOClient

.PHONY: clean

clean:
	-rm -rf *.class cn
