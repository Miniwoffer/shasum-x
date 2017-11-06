all: shasum-x

shasum-x: shasum-x.c
	gcc shasum-x.c -lssl -lcrypto -o shasum-x
