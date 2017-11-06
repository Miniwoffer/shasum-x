#include <openssl/sha.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ptheard.h>


int main(int argc, char* argv[] )
{
  unsigned char buffer[BUFSIZ];    
  int bufflen;
  for(int i = 1; i < argc; i++){
    int file = open(argv[i],O_RDONLY);
    if(file > 0){
        SHA256_CTX mysha; 
        SHA256_Init(&mysha);
        while((bufflen = read(file,buffer,BUFSIZ)) > 0){
            SHA256_Update(&mysha,buffer,bufflen);
        }
        int sharet = SHA256_Final(buffer,&mysha);
        for(int j = 0;j < 32; j++)
            printf("%02x",buffer[j]);
        printf("  %s\n",argv[i]);
    }
    else {
        printf("-  %s\n",argv[i]);
    }
  }
  return 0;
}
