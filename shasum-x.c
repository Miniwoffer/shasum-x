#include <openssl/sha.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#define HASH_SIZE 32
#define HASH_DISPLAY 16

void *sha256sum(const void* filename){ 
	unsigned char buffer[BUFSIZ];
	int bufflen;

	//the char buffer that is returned to the main thread
	char *outbuffer = (char*)calloc(HASH_SIZE,HASH_DISPLAY);
	int file = open(filename,O_RDONLY);
	
	//used as part of the string parsing
	char *itr; int i;
    if(file > 0){
        SHA256_CTX mysha; 
        SHA256_Init(&mysha);
        while((bufflen = read(file,buffer,BUFSIZ)) > 0){
            	SHA256_Update(&mysha,buffer,bufflen);
        }
        SHA256_Final(buffer,&mysha);
		itr = outbuffer;
        for(i = 0;i < HASH_SIZE; i++){
            sprintf(itr,"%02x",buffer[i]);
			itr+=2;
		}
	}
	else {
		//file not found
		sprintf(outbuffer,"-");
	}
	pthread_exit((void *)outbuffer);
}
		
int main(int argc, char* argv[] )
{
	int i;
	pthread_t files[argc-1];
	
	for(i = 1; i < argc; i++){
		if(pthread_create(&files[i-1],NULL,(void *)sha256sum,argv[i])){
			fprintf(stderr, "error creating thread\n");
			return 1;
		}
  	}
	for(i = 1; i< argc;i++){
		void *ret = NULL;;
		if(pthread_join(files[i-1],&ret)){
			fprintf(stderr, "error joining thread\n");
			continue;
		}
		printf("%s  %s\n",(char *)ret,argv[i]);
		//TODO: check if i might leak memeory
		free(ret);
	}
  	return 0;
}
