// gcc alphanumeric.c -o alphanumeric -fno-stack-protector -no-pie -z execstack -z now -m32
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

int CheckAlphanumeric(char* shellcode, unsigned int len){
    for (int i = 0; i < len; i++)
	{
        if (
            ('0' <= shellcode[i] && shellcode[i] <= '9') ||
            ('A' <= shellcode[i] && shellcode[i] <= 'Z') ||
            ('a' <= shellcode[i] && shellcode[i] <= 'z')
        )
		{
            return 1;
        }
    }
    return 0;
}

int main(){
    unsigned int len;
    char shellcode[0x50];
    void (*getshell)();
    init();

    printf("shellcode : ");
    len = read(STDIN_FILENO, shellcode, sizeof(shellcode));

    if(CheckAlphanumeric(shellcode, len)){
        getshell = shellcode;
        getshell();
    }
    else{
        puts("Nop");
        exit(0);
    }

}
