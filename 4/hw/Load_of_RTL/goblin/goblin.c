// gcc goblin.c -o goblin -fno-stack-protector -mpreferred-stack-boundary=2 -no-pie -z relro -m32
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

void gift(){
    system("gift");
}

int main(){
    char buf[0x40];

    init();
    
    // You can use read and system
    read(STDIN_FILENO, buf, 0x100);

    return 0;
}