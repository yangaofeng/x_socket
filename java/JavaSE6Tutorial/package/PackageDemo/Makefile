TARGET:=PackageDemo

$(TARGET): PackageDemo.java
	javac -d . $^

test: $(TARGET)
	java onlyfun.caterpillar.PackageDemo

.PHONY: clean

clean:
	-rm -rf onlyfun
