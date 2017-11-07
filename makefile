all: shasum-x

shasum-x: shasum-x.c
	gcc shasum-x.c -g -lssl -lcrypto -pthread -Wall -o shasum-x

debug: shasum-x
	gdb --args shasum-x shasum-x 
