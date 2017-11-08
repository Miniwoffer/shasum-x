all: shasum-x shasum-x-debug

shasum-x: shasum-x.c
	gcc shasum-x.c -g -lssl -lcrypto -pthread -Wall -o shasum-x
shasum-x-debug: shasum-x.c
	gcc shasum-x.c -lssl -lcrypto -pthread -o shasum-x-debug
debug: shasum-x-debug
	gdb --args shasum-x-debug shasum-x-debug
clean:
	rm shasum-x-debug shasum-x
