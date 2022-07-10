// gcc pie.c -o pie -fno-stack-protector
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void init(){
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
}

void vuln(){
    char buf[0x10];
    read(0, buf, 0x100);
    printf("buf : %s\n", &buf);
    read(0, buf, 0x100);
    puts("bye");
}

void win(){
    puts("EZ~");
    system("/bin/sh");
}

int main(){

    init();
    vuln();

    return 0;
}