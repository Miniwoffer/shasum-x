#include <openssl/sha.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>

void *sha256sum(const void* filename){ 
	unsigned char buffer[BUFSIZ];
	int bufflen;
	char *outbuffer = (char*)calloc(32,16);
	int file = open(filename,O_RDONLY);
    if(file > 0){
        SHA256_CTX mysha; 
        SHA256_Init(&mysha);
        while((bufflen = read(file,buffer,BUFSIZ)) > 0){
            	SHA256_Update(&mysha,buffer,bufflen);
        }
        SHA256_Final(buffer,&mysha);
		char *itr = outbuffer;
        for(int j = 0;j < 32; j++){
            sprintf(itr,"%02x",buffer[j]);
			itr+=2;
		}
	}
	else {
		sprintf(outbuffer,"-");
	}
	pthread_exit((void *)outbuffer);
}
		
int main(int argc, char* argv[] )
{
	pthread_t files[argc-1];
	
	for(int i = 1; i < argc; i++){
		if(pthread_create(&files[i-1],NULL,(void *)sha256sum,argv[i])){
			fprintf(stderr, "error creating thread\n");
			return 1;
		}
  	}
	for(int i = 1; i< argc;i++){
		void *ret = NULL;;
		if(pthread_join(files[i-1],&ret))
		{
			fprintf(stderr, "error joining thread\n");
			continue;
		}
		printf("%s  %s\n",(char *)ret,argv[i]);
		free(ret);
	}
  	return 0;
}
