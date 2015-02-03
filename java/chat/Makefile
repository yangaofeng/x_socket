all: server client

server: Server.java
	javac Server.java

client: Client.java
	javac -Xlint:deprecation Client.java

.PHONY: clean

clean:
	rm *.class -f

