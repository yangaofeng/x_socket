target: $(wildcard *.java)
	javac -cp '/root/es/root/lib/elasticsearch-1.4.4.jar' $^

.PHONY: clean test

test:
	#used same parameter with skyeyebuilder
	java -Xms4000m -Xmx4000m -XX:+UseParNewGC -XX:+UseConcMarkSweepGC -cp '.:/root/es/root/lib/elasticsearch-1.4.4.jar:/root/es/root/lib/lucene-core-4.10.3.jar' DocValue

clean:
	-rm *.class -f
	-rm *.log -f
