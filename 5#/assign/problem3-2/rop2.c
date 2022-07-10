// gcc rop2.c -o rop2 -fno-stack-protector -no-pie
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

char * bin = "/bin/sh\x00";

void tool(){

    __asm__("pop %rdx;"
            "ret;");
    __asm__("pop %rcx;"
            "ret;");
    __asm__("pop %r8;"
            "ret;");

    return;
}

void init(){
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
}

int main(){
    char buf[1024];

    init();
    puts("buf:");
    read(0, buf, 0x1024);

    return 0;
}