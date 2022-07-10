// gcc rop2.c -o rop2 -fno-stack-protector -no-pie -z relro -z now 
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
    
    puts("gets and puts need only one parameter. much easier!!");
    gets(buf);

    return 0;
}