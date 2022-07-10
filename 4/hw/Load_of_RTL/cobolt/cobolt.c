// gcc cobolt.c -o cobolt -fno-stack-protector -no-pie -z relro 
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

char binsh[8] = "/bin/sh";

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
    
    write(STDOUT_FILENO, "You can use write, read, system and /bin/sh\n", 44);
    read(STDIN_FILENO, buf, 0x100);

    return 0;
}