// gcc token.c -o token -fno-stack-protector
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int token = 0;

void init(){
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
}

int main(){
    char buf[1024];

    init();
    write(1, "buf:", 4);
    read(0, buf, 1040);

    if(token == 1){
        system("/bin/sh");
    }

    token = 1;
    return 0;
}