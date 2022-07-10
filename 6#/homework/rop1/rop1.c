// gcc rop1.c -o rop1 -fno-stack-protector -no-pie -z relro -z now -m32 -mpreferred-stack-boundary=2
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void alarm_handler() {
    exit(-1);
}

void init(){
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
    signal(SIGALRM, alarm_handler);
    alarm(30);
}

int main(){
    char buf[0x40];

    init();
    
    write(STDOUT_FILENO, "You can use read, write\n", 24);
    read(STDIN_FILENO, buf, 0x100);

    return 0;
}