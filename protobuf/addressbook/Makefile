target: addressbook writer reader
		
addressbook: addressbook.proto
	protoc --cpp_out=. ./addressbook.proto

writer: writer.cc $(wildcard *.pb.cc)
	g++  $^ -o $@ -lprotobuf

reader: reader.cc $(wildcard *.pb.cc)
	g++  $^ -o $@ -lprotobuf

.PHONY: clean

clean:
	rm -rf *.pb.h *.pb.cc writer reader
