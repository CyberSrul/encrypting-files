compiler    := gcc
linker      := ar
flags       := -Wall
executables := encode decode



encode: encode.o libcodec.so
	$(compiler) $(flags) -o encode encode.o -L. -l codec

decode: decode.o libcodec.so
	$(compiler) $(flags) -o decode decode.o -L. -l codec

libcodec.so: codec.o
	$(compiler) -shared -o libcodec.so codec.o

codec.o: codec.c codec.h
	$(compiler) $(flags) -fPIC -c codec.c

encode.o: encode.c codec.h
	$(compiler) $(flags) -c encode.c

decode.o: decode.c codec.h
	$(compiler) $(flags) -c decode.c

clean:
	rm -r *.o *.so $(executables) 2> /dev/null