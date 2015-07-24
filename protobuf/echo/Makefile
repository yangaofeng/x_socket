target: echo
		
echo: echo.proto
	protoc --cpp_out=. ./echo.proto

#writer: writer.cc $(wildcard *.pb.cc)
#	g++  $^ -o $@ -lprotobuf
#
#reader: reader.cc $(wildcard *.pb.cc)
#	g++  $^ -o $@ -lprotobuf

.PHONY: clean

clean:
	rm -rf *.pb.h *.pb.cc writer reader
