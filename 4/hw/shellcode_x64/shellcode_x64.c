// gcc shellcode_x64.c -o shellcode_x64 -fno-stack-protector -no-pie -z execstack
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
    void (*shellcode)();
    char input[0x100];

    init();

    read(STDIN_FILENO, input, 0x100);
    shellcode = input;
    shellcode();

    return 0;
}
